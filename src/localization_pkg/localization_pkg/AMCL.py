__author__ = "RoboFEI-HT"
__authors__ = "Aislan C. Almeida"
__license__ = "GNU General Public License v3.0"

from math import *
import random as rnd
from particle import *

#--------------------------------------------------------------------------------------------------
#   This class implements the Monte Carlo's Particle Filter
#   - Note that this is the augmented version, where random particles are generated when needed.
#   - As a side note, I don't like this particle reseting way, I think it is not good.
#--------------------------------------------------------------------------------------------------

class MonteCarlo():
    #----------------------------------------------------------------------------------------------
    #   Constructor of the particle filter
    #----------------------------------------------------------------------------------------------
    def __init__(self, max_qtd=0):
        # Holds the particles objects
        self.particles = []

        # Limits the quantity of particles the filter will have
        self.max_qtd = max_qtd
        self.qtd = max_qtd

        for i in range(self.qtd):
            # Randomly generates n particles
            self.particles.append(Particle())

        self.totalweight = 0 # Holds the total sum of particles' weights.

        # Coefficients used to determine if it is supposed to generate new particles.
        self.wslow = 0
        self.wfast = 0
        self.aslow = 0.1 # 0 < aslow << afast
        self.afast = 1

        self.mean = [450, 300, 0] # Holds the mean position of the estimated position.
        self.std = 0

    #----------------------------------------------------------------------------------------------
    #   Prediction step
    #----------------------------------------------------------------------------------------------
    def Prediction(self, u=None):
        # If there was movement, run the predction step
        if u != None:
            for particle in self.particles:
                particle.Motion(*u)

    #----------------------------------------------------------------------------------------------
    #   Update step
    #----------------------------------------------------------------------------------------------
    def Update(self, z=None):
        # If there was any measure, run the update step
        self.totalweight = 0

        if z != None:
            for particle in self.particles:
                self.totalweight += particle.Sensor(z)
    
    #----------------------------------------------------------------------------------------------
    #   Resample step
    #----------------------------------------------------------------------------------------------
    def Resample(self, qtd):
        parts = [] # Starts a empty list, which will hold copies of old particles
        new = [] # Starts a empty list, whihc will hold new random particles

        # Coefficients adjusments
        self.wslow += self.aslow * (self.totalweight/len(self.particles) - self.wslow)
        self.wfast += self.afast * (self.totalweight/len(self.particles) - self.wfast)

        # print self.wslow, self.wfast, self.totalweight/len(self.particles)

        step = self.totalweight / qtd # Computes the step size
        s = step/2 # the first step is given by half the total.

        m_x = 0 # Sum of x
        m_y = 0 # Sum of y
        m_s = 0 # Sum of sin of rotation
        m_c = 0 # Sum of cos of rotation
        m_count = 0 # Quantity counter

        for p in self.particles: # For each particle,
            while s < p.weight: # while the particles weight is grater than the step,
                s += step # rises the step size,
                if max(0, 1.0-self.wfast/self.wslow) > rnd.random():
                    new.append(Particle()) # generates a new random particle
                else:
                    parts.append(Particle(p.x, p.y, p.rotation)) # adds the particle to the list.
                    # Do the summing process for the mean computation
                    m_x += p.x 
                    m_y += p.y 
                    m_s += sin(radians(p.rotation))
                    m_c += cos(radians(p.rotation))
            s -= p.weight # Removes the used steps.

        oldqtd = len(parts) # Saves the quantity of particles.

        # Computes the mean dividing the sum for the quantity
        self.mean[0] = m_x / oldqtd
        self.mean[1] = m_y / oldqtd
        # computes mean rotation by finding the arctan of the sum of sins over cossins
        self.mean[2] = degrees(atan2(m_s,m_c))

        # Computes the standard deviation of particles
        sum_std = 0
        for p in parts:
            sum_std += (p.x - self.mean[0])**2 + (p.y - self.mean[1])**2
        self.std = sqrt(sum_std / oldqtd)

        # Saves the particles for the next iteration
        self.particles = parts + new
        self.qtd = len(self.particles)

    #----------------------------------------------------------------------------------------------
    #   Main algorithm
    #----------------------------------------------------------------------------------------------
    def main(self, u=None, z=None):
        self.Prediction(u)
        self.Update(z)
        self.Resample(self.max_qtd)
        return self.mean, self.std