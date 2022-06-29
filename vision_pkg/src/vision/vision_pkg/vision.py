####################################################################################################################################
# ros2 run vision_pkg vision
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
from .submodules.camvideostream import WebcamVideoStream
#import imutils
from .submodules.ClassConfig import *

#from BallVision import *
from .submodules.DNN import *

try:
    """There are differences in versions of the config parser
    For versions > 3.0 """
    from configparser import ConfigParser
except ImportError:
    """For versions < 3.0 """
    from configparser import ConfigParser 


parser = argparse.ArgumentParser(description='Robot Vision', epilog= 'Responsavel pela deteccao dos objetos em campo / Responsible for detection of Field objects')
parser.add_argument('--visionball', '--vb', action="store_true", help = 'Calibra valor para a visao da bola')
parser.add_argument('--withoutservo', '--ws', action="store_true", help = 'Servos desligado')
parser.add_argument('--head', '--he', action="store_true", help = 'Configurando parametros do controle da cabeca')


#----------------------------------------------------------------------------------------------------------------------------------


class ballStatus(Node):

    def __init__(self, config):
        self.config = config
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Vision, 'ball_position', 10)
        self.vcap = WebcamVideoStream(src=1).start() #Abrindo camera)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.thread_DNN)
        self.i = 0
        self.args2 = parser.parse_args()
        self.detectBall = objectDetect(self.args2.withoutservo, self.config)

    def __del__(self):
        self.vcap.stop()

    def BallStatus(self, x,y,status):
        msg = Vision()
        msg.ball_detected = True
        self.publisher_.publish(msg)
        print("Bola detectada '%s'" % msg.ball_detected)
        if status  == 1:
			#Bola a esquerda
            if (x <= self.config.x_left):
                msg.ball_left = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_left)

            #Bola ao centro esquerda
            if (x > self.config.x_left and x < self.config.x_center):
                msg.ball_center_left = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_center_left)

			#Bola centro direita
            if (x < self.config.x_right and x > self.config.x_center):
                msg.ball_center_right = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_center_right)

			#Bola a direita
            if (x >= self.config.x_right):
                msg.ball_right = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_right)

        else:
            if (status ==2):
                msg.ball_left = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_left)
            else:
                msg.ball_right = True
                self.publisher_.publish(msg)
                #self.get_logger().info('Publishing: "%s"' % msg.ball_right)
        print("Status:  '%s'" % status)
        print("Bola a Esquerda:  '%s'" % msg.ball_left)
        print("Bola ao Centro Esquerda '%s'" % msg.ball_center_left)
        print("Bola ao Centro Direita '%s'" % msg.ball_right)
        print("Bola a Direita '%s'" % msg.ball_center_right)
		
    #	#CUIDADO AO ALTERAR OS VALORES ABAIXO!! O código abaixo possui inversão de eixos!
	#	# O eixo em pixels é de cima para baixo ja as distancias são ao contrario.
	#	# Quanto mais alto a bola na tela menor o valor em pixels 
	#	# e mais longe estará a bola do robô
		#Bola acima
        if (y < self.config.y_longe):
            msg.ball_far = True
            self.publisher_.publish(msg)
            #self.get_logger().info('Publishing: "%s"' % msg.ball_far)
            print("Bola acima")
            self.config.max_count_lost_frame

		#Bola ao centro
        if (y < self.config.y_chute and y > self.config.y_longe):
            msg.ball_med = True
            self.publisher_.publish(msg)
            #self.get_logger().info('Publishing: "%s"' % msg.ball_med)
            print("Bola Centralizada")

		#Bola abaixo
        if (y >= self.config.y_chute):
            msg.ball_close = True
            self.publisher_.publish(msg)
            #self.get_logger().info('Publishing: "%s"' % msg.ball_close)
            print("Bola abaixo")
		
    def thread_DNN(self):
#	time.sleep(1)
#	script_start_time = time.time()
#	print "FRAME = ", time.time() - script_start_time
       
        #cut_right = 1280-config.cut_edge_image
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
    
    
    os.system("v4l2-ctl -d /dev/video1 -c focus_auto=0 && v4l2-ctl -d /dev/video1 -c focus_absolute=0")
    os.system("v4l2-ctl -d /dev/video1 -c saturation=200")#manter 200 para nao estourar LARC
    os.system("v4l2-ctl -d /dev/video1 -c brightness=2")

    rclpy.spin(ballS)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    ballS.destroy_node()
    cv2.destroyAllWindows()
    rclpy.shutdown()


if __name__ == '__main__':
    main()