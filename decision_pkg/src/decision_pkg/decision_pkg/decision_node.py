import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from dynamixel_sdk_custom_interfaces.msg import Decision 


class DecisionNode(Node):

    def __init__(self):
        super().__init__('decision_node')
        self.publisher_ = self.create_publisher(Decision, '/decision', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = Decision()
        msg.decision = 2
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.decision)


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

# has kick off: se true: vai até a bola , chuta. se false fica parsedate_to_datetime

# penalized: se true ele sai do campo (tipo o gamestate 4)

# seconds_till_unpenalized: se for 0 ele volta p campo(?)

# drop_in: se false ele joga normal, se true ele joga como drop-in 

# team_mates_with_red_card: ver se essa codição tá true p ele, se tiver ele sai do jogo. 





