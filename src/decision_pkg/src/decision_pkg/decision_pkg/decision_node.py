from time import sleep
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from dynamixel_sdk_custom_interfaces.msg import Decision 
from custom_interfaces.msg import Vision
from custom_interfaces.msg import HumanoidLeagueMsgs as GC
from std_msgs.msg import Bool
from sensor_msgs.msg import Imu

# ros2 run decision_pkg decision_node
# ros2 topic pub -1 /gamestate custom_interfaces/msg/HumanoidLeagueMsgs "{game_state: 1}"
# ros2 topic pub -1 /gamestate custom_interfaces/msg/HumanoidLeagueMsgs "{game_state: 1, secondary_state_mode: 2}"
# ros2 topic pub -1 /ball_position std_msgs/Bool "data: True"

TEAM_ROBOFEI = 7
ROBOT_NUMBER = 1 # JOGADOR, PARA GOLEIRO COLOCAR 0
LADO = 0 # 0 vira para o lado DIREITO e 1 para o lado ESQUERDO, depende de que lado o nosso time vai começar

BALL_DETECTED = False
BALL_LEFT = False
BALL_CENTER_LEFT = False
BALL_RIGHT = False
BALL_CENTER_RIGHT = False
orientation = 0
BALL_FAR = False # bola longe
BALL_CLOSE = False # bola perto
BALL_MED = False # bola centralizada
distance_to_kick = 40 #real robot
ready_goalie=False

class DecisionNode(Node):

    def __init__(self):
        super().__init__('decision_node')
        self.get_logger().info('Running Decision Node')
        self.ready_robot=False
        self.cont_vision=0
        # Publisher da decisão
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
        # Subscriber da IMU
        self.subscription_imu = self.create_subscription(
            Imu, 
            '/imu/rpy',
            self.listener_callback_imu,
            10)
        #self.timer=self.create_timer(0.5,self.timer_callback)
        self.subscription  
        self.subscription_vision
        self.subscription_imu

    def listener_callback_vision(self, msg):
        BALL_DETECTED = msg.ball_detected
        self.get_logger().info('I see the ball "%s"' % BALL_DETECTED)
        BALL_LEFT = msg.ball_left
        self.get_logger().info('Ball left "%s"' % BALL_LEFT)
        BALL_CENTER_LEFT = msg.ball_center_left
        self.get_logger().info('Ball center left "%s"' % BALL_CENTER_LEFT)
        BALL_RIGHT = msg.ball_right
        self.get_logger().info('Ball right "%s"' % BALL_RIGHT)
        BALL_CENTER_RIGHT = msg.ball_center_right
        self.get_logger().info('Ball center right "%s"' % BALL_CENTER_RIGHT)
        BALL_FAR = msg.ball_far
        self.get_logger().info('Ball far "%s"' % BALL_FAR)
        BALL_MED = msg.ball_med
        self.get_logger().info('Ball med "%s"' % BALL_MED)
        BALL_CLOSE = msg.ball_close
        self.get_logger().info('Ball close "%s"' % BALL_CLOSE)
           


    def listener_callback_imu(self, msg):
        orientation = msg.rpy_msg.vector.z
        self.get_logger().info('Orientation "%d"' % orientation)

    # def timer_callback(self):
    #     message= Decision()
    #     self.stand_still(message)
    #     sleep(10)
    #     self.walking(message) # Anda até chegar no meio de campo
    #     sleep(8)
    #     self.gait(message)
    #     sleep(4)
    #     self.turn(message, 0) # Vira para o lado direito
    #     sleep(8)
    #     if(BALL_DETECTED == False):
    #         self.search_ball(message) # Procura a bola
    #     else:
    #         if(BALL_LEFT==True):
    #             self.turn(message, 1) # Vira para o lado direito
    #             sleep(8)
    #         elif (BALL_RIGHT==True):
    #             self.turn(message, 0) # Vira para o lado direito
    #             sleep(8)
    #         if(BALL_FAR==True):
    #             self.walking(message) # Anda até chegar no meio de campo
    #             sleep(8)
    #             self.gait(message)
    #             sleep(4)
    #         if(BALL_MED==True):
    #             self.walking(message) # Anda até chegar no meio de campo
    #             sleep(4)
    #             self.gait(message)
    #             sleep(4)
    #         if(BALL_CLOSE==True and BALL_CENTER_LEFT==True):
    #             self.kicking(message, 0) # chuta com pe esquerdo
    #         if(BALL_CLOSE==True and BALL_CENTER_RIGHT==True):
    #             self.kicking(message, 1) # chuta com pe direito



    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.game_state)
        message = Decision()

        if(ROBOT_NUMBER == 1): # JOGADOR

            if(msg.game_state == 0): # Initial state - Robô parado em pé
                self.stand_still(message)
                self.get_logger().info('INITIAL: Initial State')

            elif(msg.game_state == 1): # Robô vai para a posição inicial
                if(self.ready_robot==False):
                    self.get_logger().info('READY: Go to start position')
                    self.walking(message) # Anda até chegar no meio de campo
                    sleep(8)
                    self.gait(message) 
                    sleep(3)
                    self.turn(message, LADO) # Anda até chegar no meio de campo
                    sleep(4)
                    self.ready_robot=True
                if(BALL_DETECTED == False):
                	self.search_ball(message) # Procura a bola
                else:
                    self.stand_still(message)
                
            elif(msg.game_state == 2): # Espera o jogo começar
                self.get_logger().info('SET: Keep ready')
                self.stand_still(message)


            elif(msg.game_state == 3): # Jogo começou
                if(msg.secondary_state == 6): # Penalti do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 3): # Timeout
                    self.stand_still(message)

                elif(msg.secondary_state == 1 and msg.secondary_state_team == TEAM_ROBOFEI): # Penalti nosso
                    self.search_ball(message) # Procura a bola
                    self.kicking(message, 1)

                elif(msg.secondary_state == 1 and msg.secondary_state_team != TEAM_ROBOFEI): # Penalti do outro time
                    self.stand_still(message)

                elif(msg.secondary_state == 4 and msg.secondary_state_team != TEAM_ROBOFEI): # Direct freekick do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 5 and msg.secondary_state_team != TEAM_ROBOFEI): # Indirect freekick do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 7 and msg.secondary_state_team != TEAM_ROBOFEI): # Escanteio do oponente
                    self.stand_still(message)
                
                elif(msg.secondary_state == 8): # Tiro de meta do goleiro, independente de qual time os jogadores ficam parados
                    self.stand_still(message)

                elif(msg.secondary_state == 9 and msg.secondary_state_team != TEAM_ROBOFEI): # Lateral do oponente
                    self.stand_still(message)

                elif(msg.penalized==True):
                    self.stand_still(message)

                else: 
                    if(BALL_DETECTED == False):
                        self.search_ball(message) # Procura a bola
                        self.cont_vision = self.cont_vision+1
                        if self.cont_vision>=20:
                            self.walking(message)
                            sleep(5)
                            self.gait(message) 
                            sleep(3)
                            self.cont_vision=0
                    else:
                        if(BALL_LEFT==True):
                            self.turn(message, 1) # Vira para o lado direito
                            sleep(8)
                        elif (BALL_RIGHT==True):
                            self.turn(message, 0) # Vira para o lado direito
                            sleep(8)
                        if(BALL_FAR==True):
                            self.walking(message) 
                            sleep(8)
                            self.gait(message)
                            sleep(4)
                        if(BALL_MED==True):
                            self.walking(message) 
                            sleep(4)
                            self.gait(message)
                            sleep(4)
                        if(BALL_CLOSE==True and BALL_CENTER_LEFT==True):
                            self.kicking(message, 0) # chuta com pe esquerdo
                        if(BALL_CLOSE==True and BALL_CENTER_RIGHT==True):
                            self.kicking(message, 1) # chuta com pe direito



            elif(msg.game_state == 4): # Jogo terminou, robô sai do campo
                self.stand_still(message)
        
        elif(ROBOT_NUMBER == 0): # GOLEIRO
            if(msg.game_state == 0): # Initial state - Robô parado em pé
                self.stand_still(message)
                self.get_logger().info('INITIAL: Initial State')

            elif(msg.game_state == 1): # Robô vai para a posição inicial
                self.get_logger().info('READY: Go to start position')
                if(ready_goalie==False):
                    self.walking(message) 
                    sleep(8)
                    ready_goalie=True
                if(BALL_DETECTED == False):
                	self.search_ball(message) # Procura a bola
                else:
                    self.stand_still(message)

            elif(msg.game_state == 2): # Espera o jogo começar
                self.get_logger().info('Keep ready')
                self.stand_still(message)

            elif(msg.game_state == 3): # Jogo começou
                self.search_ball(message)
                if(BALL_DETECTED == True):  # Bola achada
                    if BALL_LEFT ==  True:  
                        self.goalkeeper(message, 1) # Bola na esquerda se joga para a esquerda
                    elif BALL_RIGHT ==  True: 
                        self.goalkeeper(message, 2) # Bola na direita se joga para a direita
                    else: # A bola está alinhada, goleiro agacha
                        self.goalkeeper(message, 0) 

            elif(msg.game_state == 4): # Jogo terminou, robô sai do campo
                self.stand_still(message)


    def stand_still(self, message): # Robô em pé parado
        message.decision = 1
        self.publisher_.publish(message)
        self.get_logger().info('Publishing: "%d"' % message.decision)

    def kicking(self, message, side):
        if(side == 1): # Chuta com pé direito
            message.decision = 3 
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        else:
            message.decision = 4 # Chuta com o pé esquerdo
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        sleep(3)

    def walking(self, message):
        message.decision = 14 # Anda
        self.publisher_.publish(message)
        self.get_logger().info('Publishing: "%d"' % message.decision)

    def gait(self, message):
        message.decision = 15 # Gait
        self.publisher_.publish(message)
        self.get_logger().info('Publishing: "%d"' % message.decision)

    def search_ball(self, message):
        if(BALL_DETECTED == False):
            message.decision = 8 # Move o motor da cabeça para o robô procurar a bola
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)

    def turn(self, message, side):
        if(side == 0):
            message.decision = 5 # Direita
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        else:
            message.decision = 6 # Esquerda
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)

    def turn_around_ball(self, message, side):
        if (side == 0):
            message.decision = 9 # Horario
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        else:
            message.decision = 10 # Antihorario
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        sleep(4)

    def turn_around_ball(self, message, side):
        if (side == 0):
            message.decision = 9 # Horario
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        else:
            message.decision = 10 # Antihorario
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        sleep(4)

    def goalkeeper(sel, message, action):
        if(action == 0): # Agachar
            message.decision = 13
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        elif(action == 1): # Se joga para a esquerda
            message.decision = 11 
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        elif(action == 2): # Se joga para a direita
            message.decision = 12 
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)


def main(args=None):
    rclpy.init(args=args)

    decisionNode = DecisionNode()

    rclpy.spin(decisionNode)
    decisionNode.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
