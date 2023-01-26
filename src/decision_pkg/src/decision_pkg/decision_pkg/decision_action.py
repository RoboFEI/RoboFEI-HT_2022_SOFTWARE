import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from time import sleep

from std_msgs.msg import String
from custom_interfaces.msg import Decision 
from custom_interfaces.msg import Vision
from custom_interfaces.msg import HumanoidLeagueMsgs as GC
from custom_interfaces.msg import NeckPosition
from std_msgs.msg import Bool
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Vector3Stamped
from sensor_msgs.msg import Imu
from custom_interfaces.action import Control


# ros2 run decision_pkg decision_action
# ros2 topic pub -1 /gamestate custom_interfaces/msg/HumanoidLeagueMsgs "{game_state: 3}"
# ros2 topic pub -1 /gamestate custom_interfaces/msg/HumanoidLeagueMsgs "{game_state: 1, secondary_state_mode: 2}"
# ros2 topic pub -1 /ball_position std_msgs/Bool "data: True"
# ros2 topic pub -1 /neck_position custom_interfaces/msg/NeckPosition "{position19: 2048, position20: 2048}"

TEAM_ROBOFEI = 7
ROBOT_NUMBER = 0 # Goleiro = 1, jogadores != 1
LADO = 0 # 0 vira para o lado DIREITO e 1 para o lado ESQUERDO, depende de que lado o nosso time vai começar



class DecisionNode(Node):

    def __init__(self):
        super().__init__('decision_node')
        self.get_logger().info('Running Decision Node')
        # Subscriber do Game Controller
        self.subscription = self.create_subscription(
            GC,
            'gamestate',
            self.listener_callback,
            10)
        # Subscriber da visão 
        self.subscription_vision = self.create_subscription(
            Vision, 
            '/ball_position',
            self.listener_callback_vision,
            10)
        # Subscriber da posição dos motores do pescoço
        self.subscription_neck = self.create_subscription(
            NeckPosition, 
            '/neck_position',
            self.listener_callback_neck,
            10) 
        self.subscription_imu_gyro = self.create_subscription(
            Vector3Stamped, 
            'imu/rpy',
            self.listener_callback_imu_gyro,
            10) 
        self.subscription_imu_accel = self.create_subscription(
            Imu, 
            'imu/data',
            self.listener_callback_imu_accel,
            10) 
        self.timer=self.create_timer(0.008,self.timer_callback)
        self._action_client = ActionClient(self, Control, 'control_action')
        self.subscription  
        self.subscription_vision
        self.subscription_neck
        self.subscription_imu_gyro
        self.subscription_imu_accel
        self.BALL_DETECTED = False
        self.BALL_LEFT = False
        self.BALL_CENTER_LEFT = False
        self.BALL_RIGHT = False
        self.BALL_CENTER_RIGHT = False
        self.BALL_FAR = False # bola longe
        self.BALL_CLOSE = False # bola perto
        self.BALL_MED = False # bola centralizada
        self.distance_to_kick = 40 #real robot
        self.ready_robot=False
        self.gamestate = 0 # Initial state - Robô parado em pé
        self.secstate = 0
        self.secteam = 0
        self.penalized = False
        self.cont_falses = 0
        self.go_ball = 0
        self.has_kick_off = False
        self.game_already_started = True
        self.last_movement = 0
        self.movement = 1
        self.contador = 0
        self.contador_imu = 0
        self.fallen = False
        self.fallenFront = False
        self.fallen_side = False
        self.cont_fall_side = 0
        self.cancel = False
        self.finished = True
        

    def listener_callback_neck(self, msg):
        self.neck_position = [msg.position19, msg.position20]

    def listener_callback_imu_gyro(self, msg):
        self.gyro_z = msg.vector.z
    
    def listener_callback_imu_accel(self, msg):
        self.accel_z = msg.linear_acceleration.z
        self.accel_x = msg.linear_acceleration.x

        if (self.accel_z > 7 or self.accel_z < -7):
            self.contador_imu+=1
        else:
            self.contador_imu = 0
        self.get_logger().info('Contador IMU: "%d"' % self.contador_imu)
      
        if(self.contador_imu>=30):
            self.fallen = True # Robô caido
            if(self.accel_z < 0):  # Robô caido de frente
                self.fallenFront = True
                self.get_logger().info('Caido de frente')
            else: # Robô caido de costas
                self.fallenFront = False
                self.get_logger().info('Caido de costas')
        
        if (self.accel_x > 7 or self.accel_x < -7):
            self.cont_fall_side+=1
        else:
            self.cont_fall_side = 0
        self.get_logger().info('Contador IMU fall side: "%d"' % self.cont_fall_side)
      
        if(self.cont_fall_side>=30):
            self.get_logger().info('Caido de lado')
            self.fallen_side = True # Robô caido

    def listener_callback_vision(self, msg):
        # print("Vision Callback")
        self.BALL_DETECTED = msg.ball_detected
        self.get_logger().info('BALL "%s"' % self.BALL_DETECTED)
        self.BALL_LEFT = msg.ball_left
        self.BALL_CENTER_LEFT = msg.ball_center_left
        self.BALL_RIGHT = msg.ball_right
        self.BALL_CENTER_RIGHT = msg.ball_center_right
        self.BALL_FAR = msg.ball_far
        self.BALL_MED = msg.ball_med
        self.BALL_CLOSE = msg.ball_close

    def listener_callback(self, msg):
        self.get_logger().info('GAME STATE: "%s"' % msg.game_state)
        self.gamestate = msg.game_state
        self.secstate = msg.secondary_state
        self.secteam = msg.secondary_state_team
        # self.get_logger().info('PENALTY: "%s"' % msg.secondary_state_team)
        self.penalized = msg.penalized
        self.has_kick_off = msg.has_kick_off
        self.penaltyshoot_mode = msg.secondary_state_mode

    def send_goal(self, order):
        goal_msg = Control.Goal()
        goal_msg.action_number = order
        self._action_client.wait_for_server()

        if order != self.last_movement: # Se tiver que mudar o movimento
            if (order == 16 or order == 17 or order == 23): # Robô caído: prioridade é levantar, por isso ele cancela o que estiver fazendo
                self._send_goal_future = self.goal_handle.cancel_goal_async()
                self._send_goal_future.add_done_callback(self.cancel_done)
                self._send_goal_future = self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)
                self._send_goal_future.add_done_callback(self.goal_response_callback)
                self.last_movement = order
                self.get_logger().info('AAAAAAAAAAAAAAAA ORDER: %d' % order)

            else: # Robô não caído: espera ele terminar o que ele tava fazendo
                if self.finished == True:
                    self._send_goal_future = self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)
                    self._send_goal_future.add_done_callback(self.goal_response_callback)
                    self.last_movement = order
                    self.get_logger().info('OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO %d' % order)
                    self.get_logger().info('FINISHEDDD???? %d' % self.finished)
            self.finished = False

        else: # Mandando a mesma movimentação para o server
            if self.finished == True:
                self._send_goal_future = self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)
                self.last_movement = order
                self._send_goal_future.add_done_callback(self.goal_response_callback)
                self.get_logger().info('OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO')
                self.finished = False


    def cancel_done(self, future):
        cancel_response = future.result()
        if len(cancel_response.goals_canceling) > 0:
            self.get_logger().info('Goal successfully canceled')
        else:
            self.get_logger().info('Goal failed to cancel')

    def goal_response_callback(self, future):
        self.goal_handle = future.result()
        if not self.goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return
        
        self.get_logger().info('Goal accepted :)')

        self._get_result_future = self.goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.finished = result.finished
        # self.get_logger().info('Result: %d' % result.finished)

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        # if feedback.movements_remaining == 0:
        #     self.finished = True 
        # else:
        #     self.finished = False
        self.get_logger().info('Received feedback: %d' % feedback.movements_remaining)


    def timer_callback(self):
        if self.fallen:
            if self.fallenFront:
                self.stand_up_front()
                self.fallenFront = False
            else:
                self.stand_up_back()
            self.fallen = False
        elif self.fallen_side:
            self.stand_up_side()
            self.fallen_side = False
        else:
            if(ROBOT_NUMBER != 1): # JOGADOR
                if(self.gamestate == 0): # Initial state - Robô parado em pé
                    self.ready_robot = False
                    self.gait()
                    self.get_logger().info('INITIAL: Initial State')

                elif(self.gamestate == 1 and not self.ready_robot): # Robô vai para a posição inicial    
                    self.gait()
                    # if(self.BALL_DETECTED == False):
                    #         #print(self.contador)# if(self.BALL_DETECTED == False):
                    #         #print(self.contador)
                    #         if (self.contador >= 250):
                    #             if(self.go_ball==7):
                    #                 self.walking()
                    #                 sleep(8)
                    #                 self.go_ball = 0
                    #             elif(self.cont_falses>=4):
                    #                 self.turn(, 0)
                    #                 sleep(2)
                    #                 self.cont_falses = 0
                    #                 self.go_ball += 1
                    #             else:
                    #                 self.cont_falses += 1
                    #                 self.search_ball() # Procura a bola
                                    
                    #                 self.get_logger().info('PROCURANDOOOO')
                    #                 #print(self.cont_falses)
                    #             self.contador = 0
                    #         else:
                    #             self.contador += 1
                        
                    # else:
                    #     self.gait()
                    #     self.cont_falses = 0
                    #     self.get_logger().info('ACHEEEEEI' )
                    #         if (self.contador >= 250):
                    #             if(self.go_ball==7):
                    #                 self.walking()
                    #                 sleep(8)
                    #                 self.go_ball = 0
                    #             elif(self.cont_falses>=4):
                    #                 self.turn(, 0)
                    #                 sleep(2)
                    #                 self.cont_falses = 0
                    #                 self.go_ball += 1
                    #             else:
                    #                 self.cont_falses += 1
                    #                 self.search_ball() # Procura a bola
                                    
                    #                 self.get_logger().info('PROCURANDOOOO')
                    #                 #print(self.cont_falses)
                    #             self.contador = 0
                    #         else:
                    #             self.contador += 1
                        
                    # else:
                    #     self.gait()
                    #     self.cont_falses = 0
                    #     self.get_logger().info('ACHEEEEEI' )
                        
                    
                elif(self.gamestate == 2): # Espera o jogo começar
                    self.get_logger().info('SET: Keep ready')
                    self.gait()


                elif(self.gamestate == 3): # Jogo começou
                    # self.get_logger().info('Sec state: %d' %self.secstate)
                    # self.get_logger().info('Sec state: %d' %self.has_kick_off)
                    # if (self.has_kick_off and self.game_already_started):
                    #     if(not self.BALL_DETECTED):
                    #         self.cont_falses += 1
                    #         if(self.cont_falses >= 500):
                    #             self.search_ball() # Procura a bola
                    #             self.get_logger().info('PROCURANDOOOO ')
                            
                    #     else:
                    #         self.stand_still()
                    #         self.cont_falses = 0
                    #         self.get_logger().info('ACHEEEEEI' )
                    #         #IMPLEMENTAR COMEÇO DO JOGO PARA CHUTAR A BOLA

                    #         self.game_already_started = False

                    if(self.secstate == 6): # Penalti do oponente
                        self.gait()

                    elif(self.secstate == 3): # Timeout
                        self.gait()
                    
                    elif(self.secstate == 1 and self.has_kick_off == True): # Penalti nosso 
                        self.get_logger().info('PENALTI NOSSO')      
                        if (self.BALL_DETECTED == False):
                            self.walking()
                        else:
                            if (self.BALL_CLOSE):
                                if(self.BALL_CENTER_RIGHT):
                                    self.kick_right()
                                elif(self.BALL_CENTER_LEFT):
                                    self.kick_left()
                            else:
                                self.walking()

                            
                    elif(self.secstate == 1 and self.has_kick_off == False): # Penalti do outro time
                        self.gait()

                    elif(self.secstate == 4 and self.secteam != TEAM_ROBOFEI): # Direct freekick do oponente
                        self.gait()

                    elif(self.secstate == 5 and self.secteam != TEAM_ROBOFEI): # Indirect freekick do oponente
                        self.gait()

                    elif(self.secstate == 7 and self.secteam != TEAM_ROBOFEI): # Escanteio do oponente
                        self.gait()
                    
                    elif(self.secstate == 8): # Tiro de meta do goleiro
                        self.gait()

                    elif(self.secstate == 9 and self.secteam != TEAM_ROBOFEI): # Lateral do oponente
                        self.gait()
                            
                    elif(self.penalized==True):
                        self.gait()

                    else: 
                        if(self.BALL_DETECTED == False):
                            self.ballLeftTimes = 0
                            self.ballrightTimes = 0
                            self.get_logger().info('BALL NOT FOUND')
                            #print(self.contador)
                            if (self.contador >= 250):
                                if(self.cont_falses>=4):
                                    # self.walking()
                                    self.gait()
                                    sleep(3)
                                    self.cont_falses = 0
                                    self.go_ball += 1
                                else:
                                    self.get_logger().info('PROCURANDOOOO')
                                    self.cont_falses += 1
                                    self.search_ball() # Procura a bola
                                    sleep(1)
                                    #print(self.cont_falses)
                                self.contador = 0
                            else:
                                self.contador += 1
                                
                        else:
                            self.get_logger().info('BALL DETECTED ')
                            self.cont_falses = 0
                            self.walking()

                elif(self.gamestate == 4): # Jogo terminou, robô sai do campo
                    self.stand_still()
            
            else: # GOLEIRO
                if(self.gamestate == 0): # Initial state - Robô parado em pé
                    self.stand_still()
                    self.get_logger().info('INITIAL: Initial State')

                elif(self.gamestate == 1): # Robô vai para a posição inicial
                    self.get_logger().info('READY: Go to start position')
                    self.stand_still()

                elif(self.gamestate == 2): # Espera o jogo começar
                    self.get_logger().info('Keep ready')
                    self.stand_still()

                elif(self.gamestate == 3): # Jogo começou
                    if(self.BALL_DETECTED):
                        if (self.BALL_CLOSE or self.BALL_MED):
                            if(self.BALL_CENTER_LEFT or self.BALL_LEFT):
                                self.goalkeeper_fall_left()
                            else:
                                self.goalkeeper_fall_right()
                    else:
                        self.stand_still()

                elif(self.gamestate == 4): # Jogo terminou, robô sai do campo
                    self.stand_still()


    def stand_still(self): # Robô em pé parado
        self.send_goal(1)
        self.get_logger().info('Stand still')

    def stand_up_front(self):
        self.send_goal(17)

    def stand_up_back(self):
        self.send_goal(16)

    def stand_up_side(self):
        self.send_goal(23)

    def kick_right(self):
        self.send_goal(3)
        self.get_logger().info('Right kick')

    def kick_left(self):
        self.send_goal(4)
        self.get_logger().info('Left kick')

    def walking(self):
        self.send_goal(14) 
        self.get_logger().info('Walking')

    def gait(self):
        self.send_goal(15) 
        self.get_logger().info('Gait')

    def search_ball(self):
        self.send_goal(8)
        self.get_logger().info('Searching ball')

    def turn_right(self): # gira no seu próprio eixo
        self.send_goal(5)
        self.get_logger().info('Turn right')

    def turn_left(self): # gira no seu próprio eixo
        self.send_goal(6)
        self.get_logger().info('Turn left')

    def turn_around_ball_clockwise(self): # gira em torno da bola
        self.send_goal(9)
        self.get_logger().info('Turning around ball clockwise')
            
    def turn_around_ball_anti_clockwise(self): # gira em torno da bola
        self.send_goal(10)
        self.get_logger().info('Turning around ball anti-clockwise')

    def goalkeeper_squat(self):
        self.send_goal(13)
        self.get_logger().info('Squat')

    def goalkeeper_fall_left(self):
        self.send_goal(11)
        self.get_logger().info('Falling left')

    def goalkeeper_fall_right(self):
        self.send_goal(12)
        self.get_logger().info('Falling right')

    def turn_head_left(self):
        self.send_goal(20)
        self.get_logger().info('Turning head left')
        
    def turn_head_right(self):
        self.send_goal(21)
        self.get_logger().info('Turning head right')

    def turn_head_down(self):
        self.send_goal(22)
        self.get_logger().info('Turning head down')


def main(args=None):
    rclpy.init(args=args)

    decisionNode = DecisionNode()

    rclpy.spin(decisionNode)
    decisionNode.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()