# from particle import *
import pygame
import sys
from math import *

class Simulation():
    def __init__(self, screen):
        self.mx = 0
        self.my = 0
        self.screen = screen

        self.field = None

    def perform_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

    def display_update(self, particles):
        
        for particle in particles:
            xi = particle.x + 70
            yi = particle.y + 70
            xm = xi + 2 * cos(radians(particle.rotation))
            ym = yi - 2 * sin(radians(particle.rotation))
            xf = xm + 3 * cos(radians(particle.rotation))
            yf = ym - 3 * sin(radians(particle.rotation))
            pygame.draw.line(self.screen.background,(0,0,0),(xi,yi),(xm,ym), 1)
            pygame.draw.line(self.screen.background,(0,0,255),(xm,ym),(xf,yf), 1)

        pygame.display.flip()
