import argparse
import time
import cv2
import pandas as pd

# import the necessary packages
import imutils

import os
#import tarfile
import time
import os
import cv2
import numpy as np
import sys

#from servo import Servo

import random as rd
import tensorflow as tf

from object_detection.utils import label_map_util

from object_detection.utils import visualization_utils as vis_util

#SERVO_PAN = 19
#SERVO_TILT = 20

#SERVO_TILT_VALUE = 705 # Posicao central inicial Tilt
#SERVO_PAN_VALUE = 512 # Posicao central inicial Tilt




class objectDetect():
    CountLostFrame = 0
    Count = 0
    status =1
    statusLost = 0

    def __init__(self, withoutservo, config):
        self.withoutservo = withoutservo
        self.config = config
        
        # Path to frozen detection graph. This is the actual model that is used for the object detection.
        PATH_TO_CKPT = 'src/vision_pkg/src/vision/vision_pkg/submodules/nets/rede/frozen_inference_graph.pb'

        # List of the strings that is used to add correct label for each box.
        PATH_TO_LABELS = os.path.join('src/vision_pkg//src/vision/vision_pkg/submodules/nets/rede/object-detection.pbtxt')

        NUM_CLASSES = 1

        # Reading network file.
        self.__detection_graph = tf.Graph()
        with self.__detection_graph.as_default():
            od_graph_def = tf.compat.v1.GraphDef()
            with tf.compat.v2.io.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
                serialized_graph = fid.read()
                od_graph_def.ParseFromString(serialized_graph)
                tf.import_graph_def(od_graph_def, name='')


        label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
        categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
        self.category_index = label_map_util.create_category_index(categories)

        # Creating a section to run the detection.
        with self.__detection_graph.as_default():
            self.__sess = tf.compat.v1.Session(
                graph=self.__detection_graph,
                config=tf.compat.v1.ConfigProto(
                    intra_op_parallelism_threads=1,
                    inter_op_parallelism_threads=1
                )
            )

            self.__imagetensor = self.__detection_graph.get_tensor_by_name('image_tensor:0')
            self.__detectionboxes = self.__detection_graph.get_tensor_by_name('detection_boxes:0')
            self.__detectionscores = self.__detection_graph.get_tensor_by_name('detection_scores:0')
            self.__detectionclasses = self.__detection_graph.get_tensor_by_name('detection_classes:0')
            self.__numdetections = self.__detection_graph.get_tensor_by_name('num_detections:0')


    def searchball(self, image): 

#        start2 = time.time()
        BallFound = False
        frame, x, y, raio = self.Morphology(image )

        if (x==0 and y==0 and raio==0):
            self.CountLostFrame +=1
            print("@@@@@@@@@@@@@@@@@@@",self.CountLostFrame, self.config.max_count_lost_frame)
            if self.CountLostFrame>=self.config.max_count_lost_frame: 
                BallFound = False
                self.CountLostFrame = 0
                print("----------------------------------------------------------------------")
                print("----------------------------------------------------------------------")
                print("----------------------------------------------------------------------")
                print("--------------------------------------------------------Ball not found")
                print("----------------------------------------------------------------------")
                print("----------------------------------------------------------------------")
                print("----------------------------------------------------------------------")
                #if not self.withoutservo:
                #    self.servo.writeWord(self.config.SERVO_TILT_ID, self.servo.ADDR_PRO_GOAL_POSITION , self.config.POSITION_SERVO_TILT)
                #    self.status = self.SearchLostBall()
            self.statusLost = True
		    

        if (x!=0 and y!=0 and raio!=0):
            self.statusLost = False
            BallFound = True
            self.CountLostFrame = 0
            print('y ',y, 'x ',x ,'ball_up', self.config.when_ball_up, self.config.SERVO_TILT_ID, self.config.when_ball_down)
            #if not self.withoutservo:
            #    if y<self.config.when_ball_up:
            #        self.servo.writeWord(self.config.SERVO_TILT_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.POSITION_SERVO_TILT + self.config.head_up)
            #    if y>self.config.when_ball_down:
            #        self.servo.writeWord(self.config.SERVO_TILT_ID, self.servo.ADDR_PRO_GOAL_POSITION , self.config.POSITION_SERVO_TILT)
#----central a bola quando ela esta na area sobreposta--------
        if (self.status ==2 and x > 800): 
            self.status = 1
        #    self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.CENTER_SERVO_PAN)
            time.sleep(0.3)
            self.Count =1
        if (self.status ==0 and x < 150):
            self.status = 1
		#	self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.CENTER_SERVO_PAN)
            time.sleep(0.3)
            self.Count =1
			
		
		
#<<<<<<< HEAD
#=======



#>>>>>>> vision-UmpaLumpa
        return frame, x, y, raio, BallFound, self.status, self.statusLost

    #Varredura
   # def SearchLostBall(self):

        #if self.bkb.read_int(self.Mem,'IMU_STATE')==0:
            
            #if self.Count == 0:
            #    self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION  , self.config.CENTER_SERVO_PAN - self.config.SERVO_PAN_LEFT) #olha para a esquerda
            #    time.sleep(1)
            #    self.Count +=1
            #    return 0
            #if self.Count == 1:
            #    self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.CENTER_SERVO_PAN)#olha para o centro
            #    time.sleep(1)
            #    self.Count +=1
            #    return 1
            #if self.Count == 2:
            #    self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.CENTER_SERVO_PAN + self.config.SERVO_PAN_RIGHT)#olha para a direita 850- 440
            #    time.sleep(1)
            #    self.Count +=1
            #    return 2
            #if self.Count == 3:
            #    self.servo.writeWord(self.config.SERVO_PAN_ID,self.servo.ADDR_PRO_GOAL_POSITION , self.config.CENTER_SERVO_PAN)#olha pro centro
            #    time.sleep(1)
            #    self.Count = 0
            #    return 1


    def Morphology(self, frame):

        start3 = time.time()
        contador = 0
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image_np = np.asarray(frame)

      # Expand dimensions since the model expects images to have shape: [1, None, None, 3]
        image_np_expanded = np.expand_dims(image_np, axis=0)
        (boxes, scores, classes, num) = self.__sess.run(
            [self.__detectionboxes, self.__detectionscores, self.__detectionclasses, self.__numdetections],
            feed_dict={self.__imagetensor: image_np_expanded})
      # Visualization of the results of a detection.

        vis_util.visualize_boxes_and_labels_on_image_array(
          image_np,
          np.squeeze(boxes),
          np.squeeze(classes).astype(np.int32),
          np.squeeze(scores),
          self.category_index,
          use_normalized_coordinates=True,
          line_thickness=8)
#      plt.figure(figsize=IMAGE_SIZE)
#      plt.imshow(image_np)

        df = pd.DataFrame()
        df['classes'] = classes[0]
        df['scores'] = scores[0]
        df['boxes'] = boxes[0].tolist()

        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        if(df['scores'][0]>0.60):
            height, width = frame.shape[:2]
            print(df['boxes'][0][0])
            #      print df.head()

            #      box_coords[ymin, xmin, ymax, xmax]
            y1 = int(df['boxes'][0][0]*height)
            x1 = int(df['boxes'][0][1]*width)
            y2 = int(df['boxes'][0][2]*height)
            x2 = int(df['boxes'][0][3]*width)
            xmed = (x2-x1)/2
            ymed = (y2-y1)/2
            return frame, x2-xmed, y2-ymed, (xmed+ymed)/2

        #=================================================================================================
        return frame, 0, 0, 0





