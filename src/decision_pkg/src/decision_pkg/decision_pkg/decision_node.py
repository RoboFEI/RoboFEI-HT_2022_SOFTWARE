from time import sleep
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from custom_interfaces.msg import Decision 
from custom_interfaces.msg import Vision
from custom_interfaces.msg import HumanoidLeagueMsgs as GC
from custom_interfaces.msg import NeckPosition
from std_msgs.msg import Bool
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Vector3Stamped

# ros2 run decision_pkg decision_node
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
        self.ready_robot=False
        self.publisher_ = self.create_publisher(Decision, '/decision', 10)
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
        self.subscription_imu = self.create_subscription(
            Vector3Stamped, 
            'imu/rpy',
            self.listener_callback_imu,
            10) 
        self.timer=self.create_timer(0.008,self.timer_callback)
        self.subscription  
        self.subscription_vision
        self.subscription_neck
        self.subscription_imu
        self.BALL_DETECTED = False
        self.BALL_LEFT = False
        self.BALL_CENTER_LEFT = False
        self.BALL_RIGHT = False
        self.BALL_CENTER_RIGHT = False
        self.BALL_FAR = False # bola longe
        self.BALL_CLOSE = False # bola perto
        self.BALL_MED = False # bola centralizada
        self.distance_to_kick = 40 #real robot
        self.ready_goalie=False
        self.gamestate = 0 # Initial state - Robô parado em pé
        self.secstate = 0
        self.secteam = 0
        self.penalized = False
        self.cont_falses = 0
        self.go_ball = 0
        self.has_kick_off = False
        self.game_already_started = True
        self.last_movement = 1
        self.movement = 1
        self.contador = 0

    def listener_callback_neck(self, msg):
        self.neck_position = [msg.position19, msg.position20]

    def listener_callback_imu(self, msg):
        self.gyro_z = msg.vector.z
        # print(self.gyro_z)

    def listener_callback_vision(self, msg):
        print("Vision Callback")
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

    def timer_callback(self):
        message = Decision()
        if(ROBOT_NUMBER != 1): # JOGADOR
            if(self.gamestate == 0): # Initial state - Robô parado em pé
                self.ready_robot = False
                self.gait(message)
                self.publisher_.publish(message)
                self.get_logger().info('INITIAL: Initial State')

            elif(self.gamestate == 1 and not self.ready_robot): # Robô vai para a posição inicial                
                
                self.gait(message)
                # if(self.BALL_DETECTED == False):
                #         #print(self.contador)# if(self.BALL_DETECTED == False):
                #         #print(self.contador)
                #         if (self.contador >= 250):
                #             if(self.go_ball==7):
                #                 self.walking(message)
                #                 sleep(8)
                #                 self.go_ball = 0
                #             elif(self.cont_falses>=4):
                #                 self.turn(message, 0)
                #                 sleep(2)
                #                 self.cont_falses = 0
                #                 self.go_ball += 1
                #             else:
                #                 self.cont_falses += 1
                #                 self.search_ball(message) # Procura a bola
                                
                #                 self.get_logger().info('PROCURANDOOOO')
                #                 #print(self.cont_falses)
                #             self.contador = 0
                #         else:
                #             self.contador += 1
                	
                # else:
                #     self.gait(message)
                #     self.cont_falses = 0
                #     self.get_logger().info('ACHEEEEEI' )
                #         if (self.contador >= 250):
                #             if(self.go_ball==7):
                #                 self.walking(message)
                #                 sleep(8)
                #                 self.go_ball = 0
                #             elif(self.cont_falses>=4):
                #                 self.turn(message, 0)
                #                 sleep(2)
                #                 self.cont_falses = 0
                #                 self.go_ball += 1
                #             else:
                #                 self.cont_falses += 1
                #                 self.search_ball(message) # Procura a bola
                                
                #                 self.get_logger().info('PROCURANDOOOO')
                #                 #print(self.cont_falses)
                #             self.contador = 0
                #         else:
                #             self.contador += 1
                	
                # else:
                #     self.gait(message)
                #     self.cont_falses = 0
                #     self.get_logger().info('ACHEEEEEI' )
                    
                
            elif(self.gamestate == 2): # Espera o jogo começar
                self.get_logger().info('SET: Keep ready')
                self.gait(message)


            elif(self.gamestate == 3): # Jogo começou
                # self.get_logger().info('Sec state: %d' %self.secstate)
                # self.get_logger().info('Sec state: %d' %self.has_kick_off)
                # if (self.has_kick_off and self.game_already_started):
                #     if(not self.BALL_DETECTED):
                #         self.cont_falses += 1
                #         if(self.cont_falses >= 500):
                #             self.search_ball(message) # Procura a bola
                #             self.get_logger().info('PROCURANDOOOO ')
                        
                #     else:
                #         self.stand_still(message)
                #         self.cont_falses = 0
                #         self.get_logger().info('ACHEEEEEI' )
                #         #IMPLEMENTAR COMEÇO DO JOGO PARA CHUTAR A BOLA

                #         self.game_already_started = False

                if(self.secstate == 6): # Penalti do oponente
                    self.gait(message)

                elif(self.secstate == 3): # Timeout
                    self.gait(message)
                
                elif(self.secstate == 1 and self.has_kick_off == True): # Penalti nosso 
                    self.get_logger().info('PENALTI NOSSO')      
                    if (self.BALL_DETECTED == False):
                        self.walking(message)
                    else:
                        if (self.BALL_CLOSE):
                            if(self.BALL_CENTER_RIGHT):
                                print("direita DECISION")
                                self.kicking(message, 1)
                            elif(self.BALL_CENTER_LEFT):
                                print("esquerda DECISION")
                                self.kicking(message, 0)
                        else:
                            self.walking(message)

                        

                elif(self.secstate == 1 and self.has_kick_off == False): # Penalti do outro time
                    self.gait(message)

                elif(self.secstate == 4 and self.secteam != TEAM_ROBOFEI): # Direct freekick do oponente
                    self.gait(message)

                elif(self.secstate == 5 and self.secteam != TEAM_ROBOFEI): # Indirect freekick do oponente
                    self.gait(message)

                elif(self.secstate == 7 and self.secteam != TEAM_ROBOFEI): # Escanteio do oponente
                    self.gait(message)
                
                elif(self.secstate == 8): # Tiro de meta do goleiro
                    self.gait(message)

                elif(self.secstate == 9 and self.secteam != TEAM_ROBOFEI): # Lateral do oponente
                    self.gait(message)
                        
                elif(self.penalized==True):
                    self.gait(message)

                else: 
                    if(self.BALL_DETECTED == False):
                        self.ballLeftTimes = 0
                        self.ballrightTimes = 0
                        self.get_logger().info('BALL NOT FOUND')
                        #print(self.contador)
                        if (self.contador >= 250):
                            if(self.cont_falses>=4):
                                # self.walking(message)
                                self.gait(message)
                                sleep(3)
                                self.cont_falses = 0
                                self.go_ball += 1
                            else:
                                self.get_logger().info('PROCURANDOOOO')
                                self.cont_falses += 1
                                self.search_ball(message) # Procura a bola
                                sleep(1)


                                
                                #print(self.cont_falses)
                            self.contador = 0
                        else:
                            self.contador += 1
                            
                    else:
                        self.get_logger().info('BALL DETECTED ')
                        self.cont_falses = 0
                        self.walking(message)

                    

            elif(self.gamestate == 4): # Jogo terminou, robô sai do campo
                self.stand_still(message)
        
        else: # GOLEIRO
            if(self.gamestate == 0): # Initial state - Robô parado em pé
                self.stand_still(message)
                self.get_logger().info('INITIAL: Initial State')

            elif(self.gamestate == 1): # Robô vai para a posição inicial
                self.get_logger().info('READY: Go to start position')
                self.stand_still(message)

            elif(self.gamestate == 2): # Espera o jogo começar
                self.get_logger().info('Keep ready')
                self.stand_still(message)

            elif(self.gamestate == 3): # Jogo começou
                if(self.BALL_DETECTED):
                    if (self.BALL_CLOSE or self.BALL_MED):
                        if(self.BALL_CENTER_LEFT or self.BALL_LEFT):
                            self.goalkeeper(message, 1)
                        else:
                            self.goalkeeper(message, 2)
                else:
                    self.stand_still(message)

            elif(self.gamestate == 4): # Jogo terminou, robô sai do campo
                self.stand_still(message)

        

    def stand_still(self, message): # Robô em pé parado
        message.decision = 1
        self.publisher_.publish(message)
        self.get_logger().info('Stand still')

    def kicking(self, message, side):
        if(side == 1): # Chuta com pé direito
            message.decision = 3 
            self.publisher_.publish(message)
            self.get_logger().info('Right kick')
        else:
            message.decision = 4 # Chuta com o pé esquerdo
            self.publisher_.publish(message)
            self.get_logger().info('Left kick')

    def walking(self, message):
        message.decision = 14 # Anda
        self.publisher_.publish(message)
        self.get_logger().info('Walking')

    def gait(self, message):
        message.decision = 15 # Gait
        self.publisher_.publish(message)
        self.get_logger().info('Gait')

    def search_ball(self, message):
        message.decision = 8 # Move o motor da cabeça para o robô procurar a bola
        self.publisher_.publish(message)
        self.get_logger().info('Searching ball')

    def turn(self, message, side):
        if(side == 0):
            message.decision = 5 # Direita
            self.publisher_.publish(message)
            self.get_logger().info('Turn right')
        else:
            message.decision = 6 # Esquerda
            self.publisher_.publish(message)
            self.get_logger().info('Turn left')

    def turn_around_ball(self, message, side):
        if (side == 0):
            message.decision = 9 # Horario
            self.publisher_.publish(message)
            self.get_logger().info('Turning around ball clockwise')
        else:
            message.decision = 10 # Antihorario
            self.publisher_.publish(message)
            self.get_logger().info('Turning around ball anti-clockwise')

    def goalkeeper(self, message, action):
        if(action == 0): # Agachar
            message.decision = 13
            self.publisher_.publish(message)
            self.get_logger().info('Squat')
        elif(action == 1): # Se joga para a esquerda
            message.decision = 11 
            self.publisher_.publish(message)
            self.get_logger().info('Falling left')
        elif(action == 2): # Se joga para a direita
            message.decision = 12 
            self.publisher_.publish(message)
            self.get_logger().info('Falling right')

    def turn_head_left(self, message):
        message.decision = 20
        self.publisher_.publish(message)
        self.get_logger().info('Turning head left')
        
    def turn_head_right(self, message):
        message.decision = 21
        self.publisher_.publish(message)
        self.get_logger().info('Turning head right')

    def turn_head_down(self, message):
        message.decision = 22
        self.publisher_.publish(message)
        self.get_logger().info('Turning head down')

def main(args=None):
    rclpy.init(args=args)

    decisionNode = DecisionNode()

    rclpy.spin(decisionNode)
    decisionNode.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()