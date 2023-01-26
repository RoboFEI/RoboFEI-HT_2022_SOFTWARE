####################################################################################################################################
#  ros2 run vision_pkg vision
# Para ver o que a camera esta vendo:
# ros2 run vision_pkg vision --vb
####################################################################################################################################
from telnetlib import NOP
import rclpy
from rclpy.node import Node

#from std_msgs.msg import String
from custom_interfaces.msg import Vision

import sys
sys.path.append("./src")
import numpy as np
import cv2
import ctypes
import argparse
import time
from math import log,exp,tan,radians
from .camvideostream import WebcamVideoStream
#import imutils
from .ClassConfig import *

#from BallVision import *
from .DNN import *

try:
    """There are differences in versions of the config parser
    For versions > 3.0 """
    from configparser import ConfigParser
except ImportError:
    """For versions < 3.0 """
    from configparser import ConfigParser 


parser = argparse.ArgumentParser(description='Robot Vision', epilog= 'Responsavel pela deteccao dos objetos em campo / Responsible for detection of Field objects')
parser.add_argument('--visionball', '--vb', action="store_true", help = 'Calibra valor para a visao da bola', default=True)
parser.add_argument('--withoutservo', '--ws', action="store_true", help = 'Servos desligado', default=False)
parser.add_argument('--head', '--he', action="store_true", help = 'Configurando parametros do controle da cabeca', default=False)
parser.add_argument('--ros-args', action="store_true", help = ' ', default=True)


#----------------------------------------------------------------------------------------------------------------------------------


class ballStatus(Node):

    

    def __init__(self, config):
        self.config = config
        super().__init__('vision_node')
        self.publisher_ = self.create_publisher(Vision, '/ball_position', 10)
        self.vcap = WebcamVideoStream(src=0).start() # Abrindo camera

        # super().__init__('minimal_client_async')
        # self.cli = self.create_client(GetPosition, 'get_position')
        # while not self.cli.wait_for_service(timeout_sec=1.0):
        #     self.get_logger().info('service not available, waiting again...')
        # self.req = GetPosition.Request()

        # #client for request neck position

        # self.cli = self.create_client(GetPosition, 'get_position')

        # #Check availability
        # while not self.cli.wait_for_service(timeout_sec=1.0):
        #     self.get_logger().info('service not available, waiting again...')
            
        # self.req = GetPosition.Request()

        timer_period = 0.008  # seconds
        self.timer = self.create_timer(timer_period, self.thread_DNN)
        self.i = 0
        self.args2 = parser.parse_args()
        self.detectBall = objectDetect(self.args2.withoutservo, self.config)


    # def send_request(self, a):
    #     self.req.id = a
    #     self.future = self.cli.call_async(self.req)
    #     rclpy.spin_until_future_complete(self, self.future)
    #     return self.future.result()
        


    def BallStatus(self, x,y,status):
        msg = Vision()
        msg.ball_detected = True
        self.publisher_.publish(msg)
        print("Bola detectada '%s'" % msg.ball_detected)

        
        if status  == 1:
			#Bola a esquerda
            if (x <= self.config.x_left):
                msg.ball_close = True
                self.publisher_.publish(msg)
                print("Bola a esquerda")

			#Bola centro direita
            if (x < self.config.x_right and x > self.config.x_center):
                msg.ball_med = True
                self.publisher_.publish(msg)
                print("Bola Centralizada")

			#Bola a direita
            if (x >= self.config.x_right):
                msg.ball_far = True
                self.publisher_.publish(msg)
                print("Bola a direita")
                self.config.max_count_lost_frame

        else:
            if (status ==2):
                msg.ball_close = True
                self.publisher_.publish(msg)
                print("Bola a esquerda")
            else:
                msg.ball_far = True
                self.publisher_.publish(msg)
                print("Bola a direita")
		
		#Bola acima
        if (y < self.config.y_longe):
            msg.ball_left = True
            self.publisher_.publish(msg)
            print("Bola acima")
            self.config.max_count_lost_frame

		#Bola ao centro esquerda
        if (y > self.config.y_longe and y < self.config.x_center):
            msg.ball_center_left = True
            self.publisher_.publish(msg)
            print("Bola ao Centro Acima")

        #Bola ao centro direita
        if (y < self.config.y_chute and y > self.config.x_center):
            msg.ball_center_right = True
            self.publisher_.publish(msg)
            print("Bola ao Centro Abaixo")

		#Bola abaixo
        if (y >= self.config.y_chute):
            msg.ball_right = True
            self.publisher_.publish(msg)
            print("Bola Abaixo")


		
    def thread_DNN(self):
#	time.sleep(1)
#	script_start_time = time.time()
#	print "FRAME = ", time.time() - script_start_time
        msg=Vision()
        frame = self.vcap.read()
        #cv2.imwrite('file.jpg', frame)
        #print(frame)
        #frame = frame[:,config.cut_edge_image:cut_right]
        start1 = time.time()
    #===============================================================================
        ball = False
        frame_b, x, y, raio, ball, status, statusLost = self.detectBall.searchball(frame)
        print("tempo de varredura = ", time.time() - start1)
        #self.get_logger().info('Ball detected: "%s"' % msg.ball_detected)
        if ball == True:
            self.BallStatus(x,y,status)


        else:
            msg.ball_detected =False
            self.publisher_.publish(msg)
            print("Sem bola :( ")

        if self.args2.visionball:
            cv2.circle(frame_b, (int(x), int(y)), int(raio), (255, 0, 0), 4)
            cv2.imshow('frame_b', cv2.resize(frame_b, (720, 480)))
            if cv2.waitKey(25) & 0xFF == ord('q'):
                NOP



                

				
def main(args=None):
    rclpy.init(args=args)
    
    config = classConfig()
    ballS = ballStatus(config)
    # neck = ballS.send_request(20)
    # print("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
    # print(neck.position)
    

    
    # print(neck.position)
    os.system("v4l2-ctl -d /dev/video0 -c focus_auto=0 && v4l2-ctl -d /dev/video0 -c focus_absolute=0")
    os.system("v4l2-ctl -d /dev/video0 -c saturation=150")#manter 200 para nao estourar LARC
    os.system("v4l2-ctl -d /dev/video0 -c brightness=0")

    rclpy.spin(ballS)
    

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    ballS.destroy_node()
    cv2.destroyAllWindows()
    rclpy.shutdown()


if __name__ == '__main__':
    main()