import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Imu
from geometry_msgs.msg import Vector3Stamped  
from custom_interfaces.msg import Decision 
from custom_interfaces.msg import Localization 

from .Viewer.screen import * # Imports the environment of the viewer
from .Viewer.simulation import *
from .Viewer.world import *
from .Viewer.part import *
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


class LocalizationNode(Node):
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

        self.screen = Screen(self.args.graphs) # Creates a new screen

        if self.args.graphs:
            self.simul = Simulation(self.screen) # Creates the interface structure
            self.field = SoccerField(self.screen) # Draws the field
            self.simul.field = self.field # Passes the field to the simulation

        self.PF = MonteCarlo(5000) # Starts the Particle Filter

        self.zb = []
        self.zr = []
        self.zy = []
        self.zp = []
        self.timecount = []

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
        self.publisher_ = self.create_publisher(Localization, '/localization', 10)
        self.publisher_
        self.timer=self.create_timer(0.05,self.timer_callback)

    def listener_callback_imu(self, msg):
        self.orientation = msg.vector.z
        self.get_logger().info('Orientation "%f"' % self.orientation)

    def listener_callback_decision(self, msg):
        self.dec = msg.decision
        self.get_logger().info('Decision "%d"' % self.dec)

    def timer_callback(self):
        msg = Localization()
        print("Callback")
        z0 = 0
        z1 = 0
        z2 = 0
        z3 = 0

        # Process interactions events
        if self.args.graphs:
            self.simul.perform_events()

        u = self.GetU(self.dec)

        auxtime = time.time()
        try:
            if auxtime-self.timecount[0] > 0:
                self.timecount.pop(0)
                for zn in [self.zb, self.zr, self.zy, self.zp]:
                    zn.pop(0)
        except:
            pass
        self.timecount.append(auxtime)
        self.zb.append(64)
        self.zr.append(81)
        self.zy.append(142)
        self.zp.append(55)


        z0 = mean(self.zb)
        z1 = mean(self.zr)
        z2 = mean(self.zy)
        z3 = mean(self.zp)
        z4 = degrees(self.orientation)

        # Mounts the vector to be sent
        z = (z0, z1, z2, z3, z4)
        # print z
            
        # Performs Particle Filter's Update
        pos, std = self.PF.main(u,z)

        if self.args.log:
            print('\t\x1b[32mRobot at') # Prints header
            print ('\x1b[32m[x:\x1b[34m{} cm'.format(int(pos[0]))) #  Prints the x position
            print ('\x1b[32m| y:\x1b[34m{} cm'.format(int(pos[1]))) # Prints the y position
            print (u'\x1b[32m| \u03B8:\x1b[34m{}\u00B0'.format(int(pos[2]))) # Prints the theta
            print (u'\x1b[32m| \u03C3:\x1b[34m{} cm\x1b[32m]'.format(int(std))) # Prints the standard deviation

            # Wirte the robot's position on Black Board to be read by telemetry
            # self.bkb.write_int(self.Mem, 'LOCALIZATION_X', int(pos[0]))
            # self.bkb.write_int(self.Mem, 'LOCALIZATION_Y', int(pos[1]))
            # self.bkb.write_int(self.Mem, 'LOCALIZATION_THETA', int(pos[2]))
            # self.bkb.write_float(self.Mem, 'LOCALIZATION_RBT01_X', std)
        msg.xpos = pos[0]
        self.publisher_.publish(msg)
        msg.ypos = pos[1]
        self.publisher_.publish(msg)
        msg.theta = pos[2]
        self.publisher_.publish(msg)
        msg.standard_deviation = std
        self.publisher_.publish(msg)

        if self.args.graphs:
            # Redraws the screen background
            self.field.draw_soccer_field()

            # Draws all particles on screen
            self.simul.display_update(self.PF.particles)

        # Updates for the next clock
        self.screen.clock.tick(60)


    #----------------------------------------------------------------------------------------------
    #   This method returns a command instruction to the particles.
    #----------------------------------------------------------------------------------------------
    def GetU(self, Action):
        if Action in [1, 2, 3, 4, 7, 8, 16, 17]: # Stop or kick
            return (0,0,0,0,self.dt()) # x, y, rotacao, provavelmente algo relacionado ao tipo de movimento
        elif Action == 15: # Gait
            return (0,0,0,1,self.dt()) 
        elif Action == 14: # Fast Walk Forward
            return (20,0,0,1,self.dt()) 
        elif Action == 20: # Slow Walk Forward
            return (10,0,0,1,self.dt()) 
        elif Action == 20: # Fast Walk Backward
            return (-20,0,0,1,self.dt()) 
        elif Action == 20: # Slow Walk Backward
            return (-10,0,0,1,self.dt()) 
        elif Action == 20: # Walk Left
            return (0,-10,0,1,self.dt()) 
        elif Action == 20: # Walk Right
            return (0,10,0,1,self.dt()) 
        elif Action == 5: # Turn Right
            return (0,0,20,1,self.dt()) 
        elif Action == 6: # Turn Left
            return (0,0,-20,1,self.dt()) 
        elif Action == 10: # Turn Left Around the Ball
            return (0,-10,-20,1,self.dt()) 
        elif Action == 9: # Turn Right Around the Ball
            return (0,10,20,1,self.dt()) 
        elif Action == 16: # Get up, back up
            return (0,0,0,2,self.dt()) 
        elif Action == 15: # Get up, front up
            return (0,0,0,3,self.dt()) 
        elif Action == 11:
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

    localization = LocalizationNode()

    rclpy.spin(localization)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    localization.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()