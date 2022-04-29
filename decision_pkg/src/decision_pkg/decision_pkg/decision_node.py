import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from dynamixel_sdk_custom_interfaces.msg import Decision 
from messages.msg import HumanoidLeagueMsgs as GC
from std_msgs.msg import Bool
from sensor_msgs.msg import Imu

# ros2 run decision_pkg decision_node
# ros2 topic pub -1 /gamestate messages/msg/HumanoidLeagueMsgs "{game_state: 1}"
# ros2 topic pub -1 /gamestate messages/msg/HumanoidLeagueMsgs "{game_state: 1, secondary_state_mode: 2}"
# ros2 topic pub -1 /ball_position std_msgs/Bool "data: True"


LADO = 0 # 0 vira para o lado DIREITO e 1 para o lado ESQUERDO, depende de que lado o nosso time vai começar
BALL_DETECTED = False
BALL_LEFT = False
BALL_CENTER_LEFT = False
BALL_RIGHT = False
BALL_CENTER_RIGHT = False
orientation = 0

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
            Bool,  # Só um exemplo, vai ter a mensagem específica depois
            '/ball_position',
            self.listener_callback_vision,
            10)
        # Subscriber da IMU
        self.subscription_vision = self.create_subscription(
            Imu,  # Só um exemplo, vai ter a mensagem específica depois
            '/ball_position',
            self.listener_callback_imu,
            10)
        self.subscription  
        self.subscription_vision

    def listener_callback_vision(self, msg):
        if(msg.data == True):
            self.get_logger().info('I see the ball "%s"' % msg.data)
            BALL_DETECTED = True
        else:
            self.get_logger().info('I cant see the ball "%s"' % msg.data)
            BALL_DETECTED = False


    def listener_callback_imu(self, msg):
        orientation = msg.rpy_msg.vector.z
        self.get_logger().info('Orientation "%d"' % orientation)


    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.game_state)
        message = Decision()
        cont = 0

        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        # DIFERENCIAR GOLEIRO DO JOGADOR
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################
        #######################################################################################################################

        if(msg.game_state == 0): # Initial state - Robô parado em pé
            self.stand_still(message)

        elif(msg.game_state == 1): # Robô vai para a posição inicial
            self.stand_still(message)
            while(BALL_DETECTED) == False:
                self.walking(message) # Fica andando até achar a bola
                if BALL_DETECTED == True:  # Bola achada
                    break
            self.stand_still(message)

        elif(msg.game_state == 2): # Espera o jogo começar
            self.stand_still(message)
            while(BALL_DETECTED == False):
                self.search_ball(message) # Procura a bola
                if BALL_DETECTED == True:  # Bola achada
                # Alinha com a bola
                    if BALL_LEFT ==  True:  #30 ou 60
                        ## DA P FAZER ELE VIRAR ATÉ A BOLA FICAR NO CENTER (BALL_CENTER == TRUE)
                        self.turn_90_degrees(message, 1) # Vira para o lado esquerdo
                        break
                    elif BALL_RIGHT ==  False: #-30 ou -60
                        self.turn_90_degrees(message, 0) # Vira para o lado direito
                        break
                else: # A bola está alinhada, fica parado
                    self.stand_still(message)
                    break


        elif(msg.game_state == 3): # Jogo começou
            # Verifica se é o nosso time que começa com a bola
            if(msg.secondary_state == 0 or msg.secondary_state == 2):
                if(msg.has_kick_off == False): # Outro time que começa
                    self.search_ball(message)
                else:
                    self.walking_tempo(message, 20)
                    self.kicking(message, 1) # Chuta com o pé direito
            
                    while BALL_DETECTED == False: 
                        self.search_ball()
                        self.walking_tempo(message, 20) # EU QUE COLOQUEI ISSO, NÃO FAZIA MT SENTIDO O ROBÔ FICAR GIRANDO PARA SEMPRE NO MESMO LUGAR, SE NÃO ACHOU DÁ UMA ANDADA

                    if(BALL_DETECTED == True):
                        if(BALL_LEFT == True):
                            while(BALL_CENTER_LEFT == False):
                                self.turn(message, 0) # Se a bola tiver na esquerda, ele vira para a direita para deixar a bola centralizada
                        elif(BALL_RIGHT == True):
                            while(BALL_CENTER_RIGHT == False):
                                self.turn(message, 1) # Se a bola tiver na direita, ele vira para a esquerda para deixar a bola centralizada
                    

                    ###################### COLOCAR PARTE DA VISÃO QUE VE SE A BOLA TA PERTO OU LONGE DO ROBO
                    if orientation <= 30 and orientation >= -30:
                        self.kicking(message, 0)

                        
            


        elif(msg.game_state == 4): # Jogo terminou, robô sai do campo
            self.stand_still(message)
            self.turn_90_degrees(message, LADO)
            self.walking_tempo(message, 20) # Anda (esse tempo NÂO é em segundos)
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

    def walking_tempo(self, message, time):
        cont = 0
        while(cont<time):
            message.decision = 2 # Anda
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
            cont = cont+1
        cont = 0

    def walking(self, message):
        message.decision = 2 # Anda
        self.publisher_.publish(message)
        self.get_logger().info('Publishing: "%d"' % message.decision)

    def turn_90_degrees(self, message, side):
        cont = 0
        while(cont<10): # Vira
            if(LADO == 0):
                message.decision = 5 # Direita
                self.publisher_.publish(message)
                self.get_logger().info('Publishing: "%d"' % message.decision)
                cont = cont+1
            else:
                message.decision = 6 # Esquerda
                self.publisher_.publish(message)
                self.get_logger().info('Publishing: "%d"' % message.decision)
                cont = cont+1

    def search_ball(self, message):
        while(BALL_DETECTED == False):
            message.decision = 8 # Move o motor da cabeça para o robô procurar a bola
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
            cont = 0
            while(cont < 4):
                if (BALL_DETECTED == False):
                    self.turn_90_degrees(message, LADO) # Vira para o robô conseguir ver se a bola não está do lado dele
                    cont = cont + 1
                else:
                    break
            break

    def turn(self, message, side):
        if(LADO == 0):
            message.decision = 5 # Direita
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
            cont = cont+1
        else:
            message.decision = 6 # Esquerda
            self.publisher_.publish(message)
            self.get_logger().info('Publishing: "%d"' % message.decision)
            cont = cont+1




def main(args=None):
    rclpy.init(args=args)

    decisionNode = DecisionNode()

    rclpy.spin(decisionNode)
    decisionNode.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

# gamestate 0:
# parado

# gamestate 1: vai p posiçao inicial
#  print 'play'
# self.set_stand_still()
# time.sleep(1)
# self.set_walk_forward_slow(1000)
# time.sleep(30)
# self.set_turn_right() // ou left
# time.sleep(5)
# self.set_stand_still()
# time.sleep(10)
# VER SE O GOLEIRO COMEÇA NA POSIÇÃO

# gamestate 2:
# parado


# gamestate 3:
# joga


# gamestate 4:
# self.set_stand_still()
# time.sleep(1)
# self.set_walk_forward_slow(1000)
# time.sleep(30)
# self.set_turn_right() // ou left
# time.sleep(5)
# self.set_stand_still()
# time.sleep(10)


# secondary state:
# 0, 2- normal
# 1- walk(n seg) e chuta
# 3- msm coisa que o gamestate 4
# 4- chute forte -- verificar o secondary_state_team p ver se é nosso robo que chuta ou do adversario
# 5- chute fraco -- verificar o secondary_state_team p ver se é nosso robo que chuta ou do adversario
# 6- parado // goleiro se joga p lado -- verificar o secondary_state_team p ver se é nosso robo que chuta ou do adversario
# 7- cobra o escanteio: andar na direçao da bola? ou reconhecer onde é o escanteio e ir p lá. se posicionar e chutar
# POSSIVEL TURN RIGHT BALL (girar em torno da bola)
# 8- tiro de meta: goleiro vai até a bola e chuta
# 9- se nosso robo tocou por ultimo, vai até a bola, vira em torno dela e chuta, caso contrario fica parado
# 128 - vai até o circulo central

# #secondary_state team
# identificar (0 é nosso ou o 1) qual time tem a posse da bola parada 

# #secondary state mode
# 0- robo vai até a bola (depende se for goleiro ele faz outra coisa)
# 1- robo chuta (exemplo)
# 2- terminou

# first half: relacionado com o lado que o robo vai ta jogando, no segundo tempo muda o lado

# own's score ou team score: se mudar é pq alguem fez gol, robos vao p posição inicial

# has kick off: se true: vai até a bola , chuta. se false fica parado

# penalized: se true ele sai do campo (tipo o gamestate 4)

# seconds_till_unpenalized: se for 0 ele volta p campo(?)

# drop_in: se false ele joga normal, se true ele joga como drop-in 

# team_mates_with_red_card: ver se essa codição tá true p ele, se tiver ele sai do jogo. 