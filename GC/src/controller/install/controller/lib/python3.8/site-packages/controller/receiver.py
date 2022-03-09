
import socket
import time
import rclpy
from rclpy.node import Node

from construct import Container, ConstError

from std_msgs.msg import String,Bool
from controller.gamestate import GameState, ReturnData, GAME_CONTROLLER_RESPONSE_VERSION
from messages.msg import HumanoidLeagueMsgs as GameStateMsg
from rclpy.exceptions import ParameterNotDeclaredException
from rcl_interfaces.msg import ParameterType




class GameStateReceiver(Node):

    def __init__(self):
        super().__init__('game_controller')
        self.declare_parameter('TEAM_ROBOFEI', 8)
        self.declare_parameter('ROBOT_NUMBER', 1)
        self.team = self.get_parameter('TEAM_ROBOFEI').get_parameter_value().integer_value
        self.player = self.get_parameter('ROBOT_NUMBER').get_parameter_value().integer_value
        self.get_logger().info('We are playing as player  %d' % self.player,)
        self.get_logger().info('in team %d ' % self.team)


        self.state_publisher = self.create_publisher(GameStateMsg, 'gamestate', 1)
        self.state_gc = self.create_publisher(GameStateMsg, 'state', 1)

        self.man_penalize = False
        self.game_controller_lost_time = 20

        self.game_controller_connected_publisher = self.create_publisher(Bool,'game_controller_connected',1)

        self.declare_parameter('DEFAULT_LISTENING_HOST', '0.0.0.0')
        self.declare_parameter('GAME_CONTROLLER_LISTEN_PORT',3838)
        self.addr = (self.get_parameter('DEFAULT_LISTENING_HOST').get_parameter_value().string_value,self.get_parameter('GAME_CONTROLLER_LISTEN_PORT').get_parameter_value().integer_value)
        #self.get_logger().info('host: "%s"' % self.addr[0])
        #self.get_logger().info('port: "%d"' % self.addr[1])
        self.declare_parameter('GAME_CONTROLLER_ANSWER_PORT',3939)
        answer_port = self.get_parameter('GAME_CONTROLLER_ANSWER_PORT').get_parameter_value().integer_value

        self.state = None
        self.time = time.time()

        # The socket and whether it is still running
        self.socket = None
        self.running = True

        self._open_socket()
        self.receive_forever()

        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def _open_socket(self):
        """ Creates the socket """
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind(self.addr)
        self.socket.settimeout(2)
        self.socket2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.socket2.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    def receive_forever(self):
        """ Waits in a loop that is terminated by setting self.running = False """
        while rclpy.ok():
            try:
                self.receive_once()
            except IOError as e:
                node.get_logger().warn("Error while sending keepalive: " + str(e))


    def receive_once(self):
            #Receives a package and interprets it.
            #Calls :func:`on_new_gamestate`
            #Sends an answer to the GC
        try:
            data, peer = self.socket.recvfrom(GameState.sizeof())

            # Throws a ConstError if it doesn't work
            parsed_state = GameState.parse(data)

            # Assign the new package after it parsed successful to the state
            self.state = parsed_state
            self.time = time.time()

            # Publish that game controller received message
            msg = Bool()
            msg.data = True
            self.game_controller_connected_publisher.publish(msg)

            # Call the handler for the package
            self.on_new_gamestate(self.state)

            # Answer the GameController
            self.answer_to_gamecontroller(peer)

        except AssertionError as ae:
            self.get_logger().info(ae.message)
        except socket.timeout:
            self.get_logger().info("No GameController message received (socket timeout)") #Rever depois
        except ConstError:
            self.get_logger().warn("Parse Error: Probably using an old protocol!")
        finally:
            if self.get_time_since_last_package() > self.game_controller_lost_time:
                self.time += 5  # Resend message every five seconds
                self.get_logger().warn('No game controller messages received, allowing robot to move') #Rever depois
                msg = GameStateMsg()
                msg.gamestate = 3  # PLAYING
                self.state_publisher.publish(msg)
                self.state_gc.publish(msg)
                msg2 = Bool()
                msg2.data = False
                self.game_controller_connected_publisher.publish(msg2)


    def get_time_since_last_package(self):
        return time.time() - self.time

    def timer_callback(self):

        msg = GameStateMsg()
        msg.game_state = self.i
        self.state_publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.game_state)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    game_controller = GameStateReceiver()

    rclpy.spin(game_controller)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    game_controller.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
