
import socket
import time
import rclpy
from rclpy.node import Node

from construct import Container, ConstError

from std_msgs.msg import String,Bool
import std_msgs.msg
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
        self.get_logger().info('We are playing as player {} in team {}'.format(self.player,self.team))


        self.state_publisher = self.create_publisher(GameStateMsg, 'gamestate', 1)

        self.man_penalize = False
        self.game_controller_lost_time = 20

        self.game_controller_connected_publisher = self.create_publisher(Bool,'game_controller_connected',1)

        self.declare_parameter('DEFAULT_LISTENING_HOST', '0.0.0.0')
        self.declare_parameter('GAME_CONTROLLER_LISTEN_PORT',3838)
        self.addr = (self.get_parameter('DEFAULT_LISTENING_HOST').get_parameter_value().string_value,self.get_parameter('GAME_CONTROLLER_LISTEN_PORT').get_parameter_value().integer_value)
        #self.get_logger().info('host: "%s"' % self.addr[0])
        #self.get_logger().info('port: "%d"' % self.addr[1])
        self.declare_parameter('GAME_CONTROLLER_ANSWER_PORT',3939)
        self.answer_port = self.get_parameter('GAME_CONTROLLER_ANSWER_PORT').get_parameter_value().integer_value

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
                msg.game_state = 3  # PLAYING
                self.state_publisher.publish(msg)
                self.state_gc.publish(msg)
                msg2 = Bool()
                msg2.data = False
                self.game_controller_connected_publisher.publish(msg2)

    def answer_to_gamecontroller(self, peer):
        """ Sends a life sign to the game controller """
        return_message = 0 if self.man_penalize else 2

        data = Container(
            header=b"RGrt",
            version=GAME_CONTROLLER_RESPONSE_VERSION,
            team=self.team,
            player=self.player,
            message=return_message)
        try:
            destination = peer[0], self.answer_port
            self.get_logger().info('Sending answer to {} port {}'.format(destination[0], destination[1]))
            self.socket.sendto(ReturnData.build(data), destination)
        except Exception as e:
            self.get_logger().info("Network Error: %s" % str(e))

    def on_new_gamestate(self, state):
        """ Is called with the new game state after receiving a package.
            The information is processed and published as a standard message to a ROS topic.
            :param state: Game State
        """
        if state.teams[0].team_number == self.team:
            own_team = state.teams[0]
            rival_team = state.teams[1]
        elif state.teams[1].team_number == self.team:
            own_team = state.teams[1]
            rival_team = state.teams[0]
        else:
            self.get_logger().info('Team {} not playing, only {} and {}'.format(self.team,
                                                                      state.teams[0].team_number,
                                                                      state.teams[1].team_number))
            return

        try:
            me = own_team.players[self.player - 1]
        except IndexError:
            self.get_logger().info('Robot {} not playing'.format(self.player))
            return

        msg = GameStateMsg()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.game_state = state.game_state.intvalue
        msg.secondary_state = state.secondary_state.intvalue
        msg.secondary_state_mode = state.secondary_state_info[1]
        msg.first_half = state.first_half
        msg.own_score = own_team.score
        msg.rival_score = rival_team.score
        msg.seconds_remaining = state.seconds_remaining
        msg.secondary_seconds_remaining = state.secondary_seconds_remaining
        msg.has_kick_off = state.kickoff_team == self.team
        msg.penalized = me.penalty != 0
        msg.seconds_till_unpenalized = me.secs_till_unpenalized
        msg.secondary_state_team = state.secondary_state_info[0]
        msg.secondary_state_mode = state.secondary_state_info[1]
        msg.team_color = own_team.team_color.intvalue
        msg.drop_in_team = state.drop_in_team
        msg.drop_in_time = state.drop_in_time
        msg.penalty_shot = own_team.penalty_shot
        msg.single_shots = own_team.single_shots
        msg.coach_message = own_team.coach_message
        penalties = []
        red_cards = []
        for i in range(6):
            penalties.append(own_team.players[i].penalty != 0)
            red_cards.append(own_team.players[i].number_of_red_cards != 0)
        msg.team_mates_with_penalty = penalties
        msg.team_mates_with_red_card = red_cards
        self.state_publisher.publish(msg)

    def get_time_since_last_package(self):
        return time.time() - self.time



def main(args=None):
    rclpy.init(args=args)
    game_controller = GameStateReceiver()



if __name__ == '__main__':
    main()
