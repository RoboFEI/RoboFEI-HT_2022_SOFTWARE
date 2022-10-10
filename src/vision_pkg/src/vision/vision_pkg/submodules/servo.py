import ctypes
import os
from dynamixel_sdk import *                    # Uses Dynamixel SDK library


"""Describes Class Servo - Communicate, Write and read from Vision Servo-motors"""
class Servo(object):

    HEAD_TILT = 20
    HEAD_PAN  = 19

    # Control table address
    ADDR_PRO_TORQUE_ENABLE      = 64               # Control table address is different in Dynamixel model
    ADDR_PRO_GOAL_POSITION      = 116
    ADDR_PRO_PRESENT_POSITION   = 132

    # Protocol version
    PROTOCOL_VERSION            = 2.0               # See which protocol version is used in the Dynamixel

    # Default setting
    DXL_ID                      = 1                 # Dynamixel ID : 1
    BAUDRATE                    = 1000000             # Dynamixel default baudrate : 57600
    DEVICENAME                  = '/dev/robot/head'
    #DEVICENAME                  = '/dev/ttyUSB0'    # Check which port is being used on your controller
                                                    # ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

    TORQUE_ENABLE               = 1                 # Value for enabling the torque
    TORQUE_DISABLE              = 0                 # Value for disabling the torque
    DXL_MINIMUM_POSITION_VALUE  = 10           # Dynamixel will rotate between this value
    DXL_MAXIMUM_POSITION_VALUE  = 4000            # and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
    DXL_MOVING_STATUS_THRESHOLD = 20                # Dynamixel moving status threshold

    index = 0
    dxl_goal_position = [DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE]         # Goal position


    # Initialize PortHandler instance
    # Set the port path
    # Get methods and members of PortHandlerLinux or PortHandlerWindows
    portHandler = PortHandler(DEVICENAME)

    # Initialize PacketHandler instance
    # Set the protocol version
    # Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    packetHandler = PacketHandler(PROTOCOL_VERSION)

    """Initializes the communication with the servos"""
    def __init__(self,posTILT,posPAN):
        """print Start the Class Servo"""
        print "Start the Class Servo"
        if os.name == 'nt':
            import msvcrt
            def getch():
                return msvcrt.getch().decode()
        else:
            import sys, tty, termios
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            def getch():
                try:
                    tty.setraw(sys.stdin.fileno())
                    ch = sys.stdin.read(1)
                finally:
                    termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
                return ch


        # Open port
        if self.portHandler.openPort():
            print("Succeeded to open the port")
        else:
            print("Failed to open the port")
            print("Press any key to terminate...")
            getch()
            quit()


        # Set port baudrate
        if self.portHandler.setBaudRate(self.BAUDRATE):
            print("Succeeded to change the baudrate")
        else:
            print("Failed to change the baudrate")
            print("Press any key to terminate...")
            getch()
            quit()

        # Enable Dynamixel Torque
        dxl_comm_result, dxl_error = self.packetHandler.write1ByteTxRx(self.portHandler, self.HEAD_PAN, self.ADDR_PRO_TORQUE_ENABLE, self.TORQUE_ENABLE)
        if dxl_comm_result != COMM_SUCCESS:
            print("ERRO: %s" % self.packetHandler.getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
            print("ERRO: %s" % self.packetHandler.getRxPacketError(dxl_error))
        else:
            print("Dynamixel has been successfully connected")

        #--------------------------------------------------------------------------------------------------------------------
        #""" Define initial torque with 50% to servo ID=20, parameter 34 seted with 2048"""
        #dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(self.portHandler, HEAD_TILT, ADDR_PRO_GOAL_POSITION, posTILT)
        #if dxl_comm_result != COMM_SUCCESS:
        #    print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
        #elif dxl_error != 0:
        #    print("%s" % packetHandler.getRxPacketError(dxl_error))
        """ Define initial torque with 50% to servo ID=19, parameter 34 seted with 2048"""
        dxl_comm_result, dxl_error = self.packetHandler.write4ByteTxRx(self.portHandler, self.HEAD_PAN, self.ADDR_PRO_GOAL_POSITION, posPAN)
        if dxl_comm_result != COMM_SUCCESS:
            print("%s" % self.packetHandler.getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
            print("%s" % self.packetHandler.getRxPacketError(dxl_error))
        #--------------------------------------------------------------------------------------------------------------------
        """ Reads a byte from servo defined by ID """
    def readByte(self, ID, Pos):
        """Returns a byte from servo defined by ID in pos position"""
        data_read, result, error = self.packetHandler.read1ByteTxRx(self.portHandler, ID, Pos)
        return data_read, result, error

        """ Reads a word from servo defined by ID """
    def readWord(self, ID, Pos):
        """ Returns a word from servo defined by ID in pos position"""
        data_read, result, error = self.packetHandler.read4ByteTxRx(self.portHandler, ID, Pos)
        return data_read, result, error

        """ Writes a byte from servo defined by ID """
    def writeByte(self, ID, Pos, value):
        """ Writes a byte in servo ID, Position Pos, and the value to be written"""
        dxl_comm_result, dxl_error = self.packetHandler.write1ByteTxRx(self.portHandler, ID, Pos, value)
        return dxl_comm_result, dxl_error

        """ Writes a word from servo defined by ID """
    def writeWord(self, ID, Pos, value):
        """ Writes a word in servo ID, Position Pos, and the value to be written"""
        dxl_comm_result, dxl_error = self.packetHandler.write4ByteTxRx(self.portHandler, ID, Pos, value)
        return dxl_comm_result, dxl_error


