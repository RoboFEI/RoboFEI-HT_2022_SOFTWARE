__author__ = "RoboFEI-HT"
__authors__ = "Aislan C. Almeida"
__license__ = "GNU General Public License v3.0"

from math import *
import random as rnd
from .particle import *

#--------------------------------------------------------------------------------------------------
#   This class implements the Monte Carlo's Particle Filter
#   - Implementation of Sensor Reseting Monte Carlo Localization
#--------------------------------------------------------------------------------------------------

class MonteCarlo():
    #----------------------------------------------------------------------------------------------
    #   Constructor of the particle filter
    #----------------------------------------------------------------------------------------------
    def __init__(self, max_qtd=0, errstd=None):
        # Holds the particles objects
        self.particles = []

        # Limits the quantity of particles the filter will have
        self.max_qtd = max_qtd
        self.qtd = max_qtd

        # Standard deviation used for computing angles likelihoods, in degrees.
        if errstd == None:
            self.errstd = [5, 30]
        else:
            self.errstd == errstd

        for i in range(self.qtd):
            # Randomly generates n particles
            self.particles.append(Particle(std=errstd))

        self.totalweight = 0 # Holds the total sum of particles' weights.
        self.maxweight = 0 # Holds the weight of the best particle.

        self.mean = [450, 300, 0] # Holds the mean position of the estimated position.
        self.std = 10

    #----------------------------------------------------------------------------------------------
    #   Method that returns a probable position for the robot given its sensoring
    #----------------------------------------------------------------------------------------------
    def SensorReseting(self, z=None):
        x = [0, 100, 200, 300, 400, 500, 600, 700, 800, 900] # Grid in X position
        y = [0, 100, 200, 300, 400, 500, 600] # Grid in Y position
        k = [(0, 0), (900, 0), (0, 600), (900, 600)] # Coefficients of distance for blue, red, yellow and purple
        n = None # Landmark index

        # Return the index of the first seen landmark
        for m in range(4):
            if z[m] != -999:
                n = m
                break

        if n == None:
            return []

        P = [] # Points in the grid
        sumW = 0

        # For each point in the grid
        for i in x:
            for j in y: 
                # Computes the possible angle for the angle
                ang = degrees(atan2(j-k[n][1], k[n][0]-i) - radians(z[n]))
                # Create a particle on the point with the computed angle
                aux = Particle(i,j,ang)
                # Computes the weight given the sensors
                weight = aux.Sensor(z)
                # Appends the particle to the grid list
                P.append(aux)
                # Update with the best particle's weight
                sumW += weight

        ret = [] # Returning with possibilities
        

        # For each particle on the grid
        for part in P:
            # chooses those with the best weight
            if part.weight > sumW/(1+len(P)):
                ret.append(part)

        # Sort the particles by the weight
        ret.sort(key=lambda aux: aux.weight, reverse=True)
        # print len(ret), z
        # print threshold, '\n'
        return ret

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
        self.maxweight = 0

        if z != None:
            for particle in self.particles:
                self.totalweight += particle.Sensor(z)
                self.maxweight = max(self.maxweight, particle.weight)
    
    #----------------------------------------------------------------------------------------------
    #   Resample step
    #----------------------------------------------------------------------------------------------
    def Resample(self, qtd, z):
        parts = [] # Starts a empty list.

        step = self.totalweight / qtd # Computes the step size
        s = step/2 # the first step is given by half the total.

        m_x = 0 # Sum of x
        m_y = 0 # Sum of y
        m_s = 0 # Sum of sin of rotation
        m_c = 0 # Sum of cos of rotation

        for p in self.particles: # For each particle,
            while s < p.weight: # while the particles weight is grater than the step,
                s += step # rises the step size,
                parts.append(Particle(p.x, p.y, p.rotation)) # adds the particle to the list.
                # Do the summing process for the mean computation
                m_x += p.x 
                m_y += p.y 
                m_s += sin(radians(p.rotation))
                m_c += cos(radians(p.rotation))
            s -= p.weight # Removes the used steps.

        self.particles = parts # Overwrites the previous particles.
        self.qtd = len(self.particles) # Saves the quantity of particles.

        # Computes the mean dividing the sum for the quantity
        self.mean[0] = m_x / self.qtd
        self.mean[1] = m_y / self.qtd
        # computes mean rotation by finding the arctan of the sum of sins over cossins
        self.mean[2] = degrees(atan2(m_s,m_c))

        sum_std = 0
        for p in self.particles:
            sum_std += (p.x - self.mean[0])**2 + (p.y - self.mean[1])**2
        self.std = sqrt(sum_std / self.qtd)

        P = Particle(*self.mean)
        print (P.Sensor(z), '\t', self.std)

    #----------------------------------------------------------------------------------------------
    #   Main algorithm
    #----------------------------------------------------------------------------------------------
    def main(self, u=None, z=None):
        
        SRset = self.SensorReseting(z)
        for i in range(int(self.qtd/10)):
            # if SRset == []:
            if True:
                self.particles.append(Particle())
            else:
                aux = SRset[i % len(SRset)]
                self.particles.append(Particle(normals=[[aux.x,20],[aux.y,20],[aux.rotation,5]]))

        self.Prediction(u)
        self.Update(z)
        self.Resample(self.qtd, z)

        return self.mean, self.std