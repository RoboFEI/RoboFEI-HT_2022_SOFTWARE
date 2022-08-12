import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Imu
from geometry_msgs.msg import Vector3Stamped  
from dynamixel_sdk_custom_interfaces.msg import Decision 

from .Viewer.screen import * # Imports the environment of the viewer
import time 

# To pass arguments to the function
import argparse
try:
    from configparser import ConfigParser
except ImportError:
    from ConfigParser import ConfigParser

# To parse arguments on execution
parser = argparse.ArgumentParser(description='Robot Localization', epilog= 'Implements particle filters to self-localize a robot on the field.')
parser.add_argument('-g', '--graphs', action="store_true", help='Shows graphical interface which visualizes the particles.')
parser.add_argument('-l', '--log', action="store_true", help='Print variable logs.')
parser.add_argument('-m', '--mcl', action="store_true", help='Uses Monte-Carlo Localization')
parser.add_argument('-a', '--amcl', action="store_true", help='Uses Augmented Monte-Carlo Localization')
parser.add_argument('-s', '--srmcl', action="store_true", help='Uses Sensor Reseting Monte-Carlo Localization')

args = parser.parse_args()

if args.mcl:
    from .MCL import *
elif args.amcl:
    from .AMCL import *
elif args.srmcl:
    from .SRMCL import *
else:
    print('Please choose a version of MCL to be used!')
    exit()


#--------------------------------------------------------------------------------------------------
#   Class implementing the Core of the Localization Process
#--------------------------------------------------


class Localization(Node):
    #----------------------------------------------------------------------------------------------
    #   Class constructor and pre-processing.
    #----------------------------------------------------------------------------------------------
    def __init__(self):
        super().__init__('localization')
        self.get_logger().info('Running Localization Node')

        self.orientation = 0
        self.dec = 0

        config = ConfigParser()   # Configuration file
        try:
            config.read('../../Control/Data/config.ini') # Reads the config archive
        except:
            print ("#----------------------------------#")
            print ("#   Error loading config parser.   #")
            print ("#----------------------------------#")

        self.args = parser.parse_args()

        # Timestamp to use on the time step used for motion
        self.timestamp = time.time()

        screen = Screen(self.args.graphs) # Creates a new screen

        if self.args.graphs:
            simul = Simulation(screen) # Creates the interface structure
            field = SoccerField(screen) # Draws the field
            simul.field = field # Passes the field to the simulation

        PF = MonteCarlo(5000) # Starts the Particle Filter

        print("AQUI")

        zb = []
        zr = []
        zy = []
        zp = []
        timecount = []

        self.subscription_imu = self.create_subscription(
            Vector3Stamped, 
            '/imu/rpy',
            self.listener_callback_imu,
            10)
        self.subscription_imu  # prevent unused variable warning
        self.subscription_decision = self.create_subscription(
            Decision, 
            '/decision',
            self.listener_callback_decision,
            10)
        self.subscription_decision
        self.timer=self.create_timer(0.05,self.timer_callback)

    def listener_callback_imu(self, msg):
        self.orientation = msg.vector.z
        self.get_logger().info('Orientation "%f"' % self.orientation)

    def listener_callback_decision(self, msg):
        self.dec = msg.decision
        self.get_logger().info('Decision "%d"' % self.dec)

    def timer_callback(self):
        z0 = 0
        z1 = 0
        z2 = 0
        z3 = 0

        # Process interactions events
        if self.args.graphs:
            simul.perform_events()

        u = self.GetU(self.dec)

        auxtime = time.time()
            try:
                if auxtime-timecount[0] > 0:
                    timecount.pop(0)
                    for zn in [zb, zr, zy, zp]:
                        zn.pop(0)
            except:
                pass

    #----------------------------------------------------------------------------------------------
    #   This method returns a command instruction to the particles.
    #----------------------------------------------------------------------------------------------
    def GetU(self, Action):
        if Action in [0, 4, 5, 12, 13, 19, 20, 21, 22]:
            return (0,0,0,0,self.dt()) # Stop or kick
        elif Action == 11:
            return (0,0,0,1,self.dt()) # Gait
        elif Action == 1:
            return (20,0,0,1,self.dt()) # Fast Walk Forward
        elif Action == 8:
            return (10,0,0,1,self.dt()) # Slow Walk Forward
        elif Action == 17:
            return (-20,0,0,1,self.dt()) # Fast Walk Backward
        elif Action == 18:
            return (-10,0,0,1,self.dt()) # Slow Walk Backward
        elif Action == 6:
            return (0,-10,0,1,self.dt()) # Walk Left
        elif Action == 7:
            return (0,10,0,1,self.dt()) # Walk Right
        elif Action == 2:
            return (0,0,20,1,self.dt()) # Turn Right
        elif Action == 3:
            return (0,0,-20,1,self.dt()) # Turn Left
        elif Action == 9:
            return (0,-10,-20,1,self.dt()) # Turn Left Around the Ball
        elif Action == 14:
            return (0,10,20,1,self.dt()) # Turn Right Around the Ball
        elif Action == 16:
            return (0,0,0,2,self.dt()) # Get up, back up
        elif Action == 15:
            return (0,0,0,3,self.dt()) # Get up, front up
        elif Action == 10:
            print ("ERROR - Please, edit Localization.GetU() for Goalkeeper before resuming!")
            return (0,0,0,0,self.dt())

    #----------------------------------------------------------------------------------------------
    #   This method returns the time since the last update
    #----------------------------------------------------------------------------------------------
    def dt(self):
        auxtime = time.time()
        timer = auxtime - self.timestamp
        self.timestamp = auxtime
        return timer

def mean(vec):
    s = 0
    n = 0
    m = 0
    for x in vec:
        if x != -999:
            n += 1
            s += x*n
            m += n
    if n == 0:
        return -999
    else:
        return s/m

def main(args=None):
    rclpy.init(args=args)

    localization = Localization()

    rclpy.spin(localization)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    localization.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()