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
# ros2 topic pub -1 /gamestate messages/msg/HumanoidLeagueMsgs "{game_state: 1}"
# ros2 topic pub -1 /gamestate messages/msg/HumanoidLeagueMsgs "{game_state: 1, secondary_state_mode: 2}"
# ros2 topic pub -1 /ball_position std_msgs/Bool "data: True"

TEAM_ROBOFEI = 22
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

class DecisionNode(Node):

    def __init__(self):
        super().__init__('decision_node')
        self.get_logger().info('Running Decision Node')
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
        self.subscription_vision = self.create_subscription(
            Imu, 
            '/imu/rpy',
            self.listener_callback_imu,
            10)
        self.subscription  
        self.subscription_vision

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

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.game_state)
        message = Decision()

        if(ROBOT_NUMBER == 1): # JOGADOR

            if(msg.game_state == 0): # Initial state - Robô parado em pé
                self.stand_still(message)
                self.get_logger().info('Initial State')

            elif(msg.game_state == 1): # Robô vai para a posição inicial
                self.get_logger().info('Go to start position')
                if(BALL_DETECTED == False):
                    self.walking_tempo(message, 20) # Anda até chegar no meio de campo
                for x in range(0,3):
                	if(BALL_DETECTED == False):
                		self.search_ball(message) # Procura a bola, no primeiro vira a cabeça p esq, depois volta p meio e dps p dir
                self.stand_still(message)
                
                

            elif(msg.game_state == 2): # Espera o jogo começar
                self.get_logger().info('Keep ready')
                if msg.game_state != 2:  # Mudou de estado
                    self.stand_still(message)
                elif BALL_DETECTED == True:  # Bola achada
                # Alinha com a bola
                    self.get_logger().info('Achou a bola')
                    if BALL_LEFT ==  True:  #30 ou 60
                        self.get_logger().info('Bola na esquerda')
                        self.turn(message, 1) # Vira para o lado esquerdo
                    elif BALL_RIGHT ==  True: #-30 ou -60
                        self.get_logger().info('Bola na direita')
                        self.turn(message, 0) # Vira para o lado direito
                    else: # A bola está alinhada, fica parado
                        self.get_logger().info('Bola alinhada')
                        self.stand_still(message)
                else:
                    self.search_ball(message) # Procura a bola
                    self.get_logger().info('Ball not detected and game state 2')


            elif(msg.game_state == 3): # Jogo começou
                if(msg.secondary_state == 6): # Penalti do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 3): # Timeout
                    self.stand_still(message)
                    ## COLOCAR IMU TALVEZ P ROBO IR P LATERAL MSM
                    self.turn(message, LADO)
                    self.walking_tempo(message) # Anda (esse tempo NÂO é em segundos)
                    self.stand_still(message)

                elif(msg.secondary_state == 1 and msg.secondary_state_team == TEAM_ROBOFEI): # Penalti nosso
                    self.search_ball(message) # Procura a bola
                    self.walking_tempo(message, 20)
                    self.kicking(message, 1)

                elif(msg.secondary_state == 1 and msg.secondary_state_team != TEAM_ROBOFEI): # Penalti do outro time
                    self.stand_still(message)

                elif(msg.secondary_state == 4 and msg.secondary_state_team == TEAM_ROBOFEI): # Direct freekick nosso
                    self.search_ball(message) # Procura a bola
                    self.walking_tempo(message, 20)
                    self.kicking(message, 1)

                elif(msg.secondary_state == 4 and msg.secondary_state_team != TEAM_ROBOFEI): # Direct freekick do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 5 and msg.secondary_state_team == TEAM_ROBOFEI): # Indirect freekick nosso
                    self.search_ball(message) # Procura a bola
                    self.walking_tempo(message, 20)
                    self.kicking(message, 1)

                elif(msg.secondary_state == 5 and msg.secondary_state_team != TEAM_ROBOFEI): # Indirect freekick do oponente
                    self.stand_still(message)

                elif(msg.secondary_state == 7 and msg.secondary_state_team != TEAM_ROBOFEI): # Escanteio do oponente
                    self.stand_still(message)
                
                elif(msg.secondary_state == 8): # Tiro de meta do goleiro, independente de qual time os jogadores ficam parados
                    self.stand_still(message)

                elif(msg.secondary_state == 9 and msg.secondary_state_team != TEAM_ROBOFEI): # Lateral do oponente
                    self.stand_still(message)

                else: 
                    #if(msg.secondary_state == 0 or msg.secondary_state == 2):
                    if(msg.has_kick_off == True): # Nosso kick off
                        self.walking_tempo(message, 10)
                        self.kicking(message, 1) # Chuta com o pé direito
                
                    if BALL_DETECTED == False: 
                        self.search_ball(message)
                        if(BALL_DETECTED == False):
                            for x in (0, 4):
                                self.turn(message, LADO)
                            self.walking_tempo(message, 20) # EU QUE COLOQUEI ISSO, NÃO FAZIA MT SENTIDO O ROBÔ FICAR GIRANDO PARA SEMPRE NO MESMO LUGAR, SE NÃO ACHOU DÁ UMA ANDADA


                    elif(BALL_DETECTED == True):
                        if(BALL_LEFT == True):
                            if(BALL_CENTER_LEFT == False):
                                self.turn(message, 0) # Se a bola tiver na esquerda, ele vira para a direita para deixar a bola centralizada
                        elif(BALL_RIGHT == True):
                            if(BALL_CENTER_RIGHT == False):
                                self.turn(message, 1) # Se a bola tiver na direita, ele vira para a esquerda para deixar a bola centralizada

                        if BALL_CLOSE == True and BALL_CENTER_RIGHT == True:
                            if orientation <= 30 and orientation >= -30:
                                self.kicking(message, 1)

                            elif self.get_orientation() > 30:
                                self.turn_around_ball(message, 0) # Horario

                            elif self.get_orientation() < -30:
                                self.turn_around_ball(message, 1)

                        elif BALL_CLOSE == True and BALL_CENTER_LEFT == True:
                            if orientation <= 30 and orientation >= -30:
                                self.kicking(message, 0)
                            elif self.get_orientation() > 30:
                                self.turn_around_ball(message, 0) # Horario
                            elif self.get_orientation() < -30:
                                self.turn_around_ball(message, 1)

                        elif BALL_FAR == True or BALL_MED == True: # longe
                            self.walking(message)
                        else:
                            self.walking(message)


            elif(msg.game_state == 4): # Jogo terminou, robô sai do campo
                self.stand_still(message)
                ## COLOCAR IMU TALVEZ P ROBO IR P LATERAL MSM
                self.turn(message, LADO)
                self.walking_tempo(message, 20) # Anda (esse tempo NÂO é em segundos)
                self.stand_still(message)
                sleep(100)
        
        elif(ROBOT_NUMBER == 0): # GOLEIRO
            if(msg.game_state == 0): # Initial state - Robô parado em pé
                self.stand_still(message)
                self.get_logger().info('Initial State')

            elif(msg.game_state == 1): # Robô vai para a posição inicial
                self.get_logger().info('Go to start position')
                if(BALL_DETECTED == False):
                    self.walking_tempo(message, 20) # Anda até chegar no meio de campo
                self.search_ball(message) # Procura a bola
                self.stand_still(message)

            elif(msg.game_state == 2): # Espera o jogo começar
                self.get_logger().info('Keep ready')
                if msg.game_state != 2:  # Mudou de estado
                    self.stand_still(message)
                elif BALL_DETECTED == True:  # Bola achada
                # Alinha com a bola
                    self.get_logger().info('Achou a bola')
                    if BALL_LEFT ==  True:  #30 ou 60
                        self.get_logger().info('Bola na esquerda')
                        self.turn(message, 1) # Vira para o lado esquerdo
                    elif BALL_RIGHT ==  True: #-30 ou -60
                        self.get_logger().info('Bola na direita')
                        self.turn(message, 0) # Vira para o lado direito
                    else: # A bola está alinhada, fica parado
                        self.get_logger().info('Bola alinhada')
                        self.stand_still(message)
                else:
                    self.search_ball(message) # Procura a bola
                    self.get_logger().info('Ball not detected and game state 2')

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
                ## COLOCAR IMU TALVEZ P ROBO IR P LATERAL MSM
                self.turn(message, LADO)
                self.walking_tempo(message, 20) # Anda (esse tempo NÂO é em segundos)
                self.stand_still(message)
                sleep(100)


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

    def walking_tempo(self, message, time):
        cont = 0
        while(cont<time):
            message.decision = 14 # Anda
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
            cont = cont+1
        cont = 0

    def walking(self, message):
        message.decision = 14 # Anda
        self.publisher_.publish(message)
        self.get_logger().info('Publishing: "%d"' % message.decision)

    def search_ball(self, message):
        if(BALL_DETECTED == False):
            message.decision = 8 # Move o motor da cabeça para o robô procurar a bola
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
        sleep(3)

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
