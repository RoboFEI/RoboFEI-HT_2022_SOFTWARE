#!/usr/bin/env python

import math

from OpenGL.GL import *
from OpenGL.GLU import *
from PyQt4 import QtCore, QtGui
from PyQt4.QtOpenGL import *

try:
    from configparser import ConfigParser
except ImportError:
    from ConfigParser import ConfigParser  # ver. < 3.0

#looking for the library SharedMemory
import sys
sys.path.append('../../Blackboard/src/')
from SharedMemory import SharedMemory

#from SharedMemory import SharedMemory as blackboard
#from pygame.locals import *
#from controlRobot import *
#import pygame
#from pygame.locals import *

yaw_mode = True

#Esta eh a classe que faz o prisma em openGL========
class SpiralWidget(QGLWidget):
    '''
    Widget for drawing two spirals.
    '''
    #import os
    #os.system("pwd")

    # instantiate:
    config = ConfigParser()

    # looking for the file config.ini:
    config.read('../Data/config.ini')

    mem_key = int(config.get('Communication', 'no_player_robofei'))*100

    #Instantiate the BlackBoard's class:
    bkb = SharedMemory()
    mem = bkb.shd_constructor(mem_key)

    #bkb = SharedMemory() #Init class BlackBoard

    ax = bkb.read_float(mem, "IMU_EULER_X")
    ay = -bkb.read_float(mem, "IMU_EULER_Y")
    az = bkb.read_float(mem, "IMU_EULER_Z")

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
#        self.initializeGL()

    def resizeGL(self, width=0, height=0):
        '''
        Resize the GL window 
        '''
        if height==0:
            height=1
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(45, 1.0*width/height, 0.1, 100.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
#        print "resize"

    def initializeGL(self):
        '''
        Initialize GL
        '''

        glShadeModel(GL_SMOOTH)
        glClearColor(0.0, 0.0, 0.0, 0.0)
        glClearDepth(1.0)
        glEnable(GL_DEPTH_TEST)
        glDepthFunc(GL_LEQUAL)
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
#        print "init"

#    def drawText(self, position, textString):     
#        font = pygame.font.SysFont ("Courier", 18, True)
#        textSurface = font.render(textString, True, (255,255,255,255), (0,0,0,255))     
#        textData = pygame.image.tostring(textSurface, "RGBA", True)     
#        glRasterPos3d(*position)     
#        glDrawPixels(textSurface.get_width(), textSurface.get_height(), GL_RGBA, GL_UNSIGNED_BYTE, textData)

    def paintGL(self):
        '''
        Drawing routine
        ''' 

        global rquad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
        
        glLoadIdentity()
        glTranslatef(0,0.0,-7.0)

#        osd_text = "pitch: " + str("{0:.2f}".format(ay)) + ", roll: " + str("{0:.2f}".format(ax))

#        if yaw_mode:
#            osd_line = osd_text + ", yaw: " + str("{0:.2f}".format(az))
#        else:
#            osd_line = osd_text

#        self.drawText((-2,-2, 2), osd_line)

        # the way I'm holding the IMU board, X and Y axis are switched 
        # with respect to the OpenGL coordinate system
        if yaw_mode:                             # experimental
            glRotatef(self.az, 0.0, 1.0, 0.0)  # Yaw,   rotate around y-axis
        else:
            glRotatef(0.0, 0.0, 1.0, 0.0)
        glRotatef(self.ay ,1.0,0.0,0.0)        # Pitch, rotate around x-axis
        glRotatef(-1*self.ax ,0.0,0.0,1.0)     # Roll,  rotate around z-axis

        glBegin(GL_QUADS)	
        glColor3f(0.0,1.0,0.0)
        glVertex3f( 1.0, 0.2,-1.0)
        glVertex3f(-1.0, 0.2,-1.0)		
        glVertex3f(-1.0, 0.2, 1.0)		
        glVertex3f( 1.0, 0.2, 1.0)		

        glColor3f(1.0,0.5,0.0)	
        glVertex3f( 1.0,-0.2, 1.0)
        glVertex3f(-1.0,-0.2, 1.0)		
        glVertex3f(-1.0,-0.2,-1.0)		
        glVertex3f( 1.0,-0.2,-1.0)		

        glColor3f(1.0,0.0,0.0)		
        glVertex3f( 1.0, 0.2, 1.0)
        glVertex3f(-1.0, 0.2, 1.0)		
        glVertex3f(-1.0,-0.2, 1.0)		
        glVertex3f( 1.0,-0.2, 1.0)		

        glColor3f(1.0,1.0,0.0)	
        glVertex3f( 1.0,-0.2,-1.0)
        glVertex3f(-1.0,-0.2,-1.0)
        glVertex3f(-1.0, 0.2,-1.0)		
        glVertex3f( 1.0, 0.2,-1.0)		

        glColor3f(0.0,0.0,1.0)	
        glVertex3f(-1.0, 0.2, 1.0)
        glVertex3f(-1.0, 0.2,-1.0)		
        glVertex3f(-1.0,-0.2,-1.0)		
        glVertex3f(-1.0,-0.2, 1.0)		

        glColor3f(1.0,0.0,1.0)	
        glVertex3f( 1.0, 0.2,-1.0)
        glVertex3f( 1.0, 0.2, 1.0)
        glVertex3f( 1.0,-0.2, 1.0)		
        glVertex3f( 1.0,-0.2,-1.0)		
        glEnd()
#        print self.ax
             
    def read_data(self):
        self.ax = self.bkb.read_float(self.mem, "IMU_EULER_X")
        self.ay = -self.bkb.read_float(self.mem, "IMU_EULER_Y")
        self.az = self.bkb.read_float(self.mem, "IMU_EULER_Z")
        line_done = 0

        # request data by sending a dot
    #    ser.write(".")
        #while not line_done:
    #    line = ser.readline() 
        angles = [self.ax*180/3.1415,
                  self.ay*180/3.1415, 
                  self.az*180/3.1415]  #line.split(", ")
        if len(angles) == 3:    
            self.ax = float(angles[0])
            self.ay = float(angles[1])
            self.az = float(angles[2])
            line_done = 1
