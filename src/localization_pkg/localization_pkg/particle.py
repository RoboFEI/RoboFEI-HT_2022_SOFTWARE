__author__ = "RoboFEI-HT"
__authors__ = "Aislan C. Almeida"
__license__ = "GNU General Public License v3.0"

from math import *
import random as rnd

#--------------------------------------------------------------------------------------------------
#   Class implementing a particle used on Particle Filter Localization
#--------------------------------------------------------------------------------------------------

class Particle(object):
    #----------------------------------------------------------------------------------------------
    #   Particle constructor
    #----------------------------------------------------------------------------------------------
    def __init__(self, x=None, y=None, rotation=None, weight=1, normals=None, regions=None, a=None, std=None, spread=1):
        
        # This block sets the initial position values of the particles.
        #    If there was any given value, adopt it;
        #    else if there was a gaussian possible position given, generate a random position;
        #    else create a totally random one.

        # Note: normals is a 3x2 matrix, where
        #    the first line presents the mean and standard deviation of the x position
        #    the second line presents the mean and standard deviation of the y position
        #    the third line presents the mean and standard deviation of the rotation

        # Note2: regions is a 3x2 matrix, where
        #    the first line presents the min and max values of the x position
        #    the second line presents the min and max values of the y position
        #    the third line presents the min and max values of the rotation

        # Note3: spread determines how much the particles will spread

        # Note4: std is a vector with the values used as standard deviation for computing particles' likelihood.
        #    the first for is used for the landmarks, in sequence blue, red, yellow, purple
        #    the last one is used for the IMU orientation

        if regions == None:
            regions = ((0, 900), (0, 600), (-180, 180))

        if x != None:
            self.x = x
        elif normals:
            self.x = rnd.gauss(normals[0][0], normals[0][1])
        else:
            self.x = rnd.randint(regions[0][0], regions[0][1])

        if y != None:
            self.y = y
        elif normals:
            self.y = rnd.gauss(normals[1][0], normals[1][1])
        else:
            self.y = rnd.randint(regions[1][0], regions[1][1])

        if rotation != None:
            self.rotation = rotation
        elif normals:
            self.rotation = rnd.gauss(normals[2][0], normals[2][1])
        else:
            self.rotation = rnd.randint(regions[2][0], regions[2][1])
        
        self.weight = weight # Holds particles weight, can come from previous iterations

        spread = 1
        # Motion error coefficients
        if a == None:
            a = []
            a.append(rnd.gauss(spread*0.0007,0.0002*spread)) # a0 e-3
            a.append(rnd.gauss(spread*0.0007,0.0002*spread)) # a1 e-3
            a.append(rnd.gauss(spread*7,2*spread)) # a2 e+1
            a.append(rnd.gauss(spread*7,2*spread)) # a3 e+1

            a.append(rnd.gauss(spread*0.0007,0.0002*spread)) # a4 e-3
            a.append(rnd.gauss(spread*0.0007,0.0002*spread)) # a5 e-3
            a.append(rnd.gauss(spread*7,2*spread)) # a6 e+1
            a.append(rnd.gauss(spread*7,2*spread)) # a7 e+1

            a.append(rnd.gauss(spread*0.000007,0.000002*spread)) # a8 e-5  
            a.append(rnd.gauss(spread*0.000007,0.000002*spread)) # a9 e-5 
            a.append(rnd.gauss(spread*0.07,0.02*spread)) # a10 e-1
            a.append(rnd.gauss(spread*0.07,0.02*spread)) # a11 e-1

            a.append(rnd.gauss(spread*0.000007,0.000002*spread)) # a12 e-5
            a.append(rnd.gauss(spread*0.000007,0.000002*spread)) # a13 e-5
            a.append(rnd.gauss(spread*0.07,0.02*spread)) # a14 e-1
            a.append(rnd.gauss(spread*0.07,0.02*spread)) # a15 e-1
            # self.a = (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
            self.a = a
        else:
            self.a = a

        # Standard deviation used for computing angles likelihoods, in degrees.
        if std == None:
            self.std = [5, 30]
        else:
            self.std == std

    #----------------------------------------------------------------------------------------------
    #   Method that chooses which movement should be used
    #----------------------------------------------------------------------------------------------
    def Movement(self, straight=0, drift=0, rotational=0, moving=1, dt=0):
        if moving == 1:
            self.Motion(straight, drift, rotational, moving, dt)
        elif moving == 2:
            self.GetUpBackUp()
        elif moving == 3:
            self.GetUpFrontUp()

    #----------------------------------------------------------------------------------------------
    #   Method which moves particles around, reimplement.
    #----------------------------------------------------------------------------------------------
    def Motion(self, straight=0, drift=0, rotational=0, moving=1, dt=0):
        # straight is the robot's forward speed in cm/s
        # drift is the robot's sideways speed in cm/s
        # rotational is the robot's angular speed in degrees/s
        # moving is a boolean which caracterizes a moving robot.

        rtt = radians(rotational) # converts rotational from degrees to radians
        
        # Adds a gaussian error to thhe forward speed
        F = rnd.gauss(straight, self.a[0]*straight**2 + self.a[1]*drift**2 + self.a[2]*rtt**2 + self.a[3]*moving)
        # Adds a gaussian error to the drift speed
        D = rnd.gauss(drift, self.a[4]*straight**2 + self.a[5]*drift**2 + self.a[6]*rtt**2 + self.a[7]*moving)
        # Adds a gaussian error to the rotational speed
        W = rnd.gauss(rtt, self.a[8]*straight**2 + self.a[9]*drift**2 + self.a[10]*rtt**2 + self.a[11]*moving)
        # Adds an error to the final rotational position
        g = rnd.gauss(0, self.a[12]*straight**2 + self.a[13]*drift**2 + self.a[14]*rtt**2 + self.a[15]*moving)        

        theta = radians(self.rotation) # converts particle's rotation to radians.

        # In case of angle been smaller than 1 degree, execute this part
        if degrees(abs(W)) < 1:
            self.x += (D*sin(theta) + F*cos(theta))*dt # X position motion
            self.y += (D*cos(theta) - F*sin(theta))*dt # Y position motion
        else:
            # Computes new x and y position using movement in arcs.
            self.x += - F/W*sin(theta) + F/W*sin(theta+W*dt) - D/W*cos(-theta) + D/W*cos(-theta+W*dt)
            self.y += -F/W*cos(theta) + F/W*cos(theta+W*dt) - D/W*sin(-theta) + D/W*sin(-theta+W*dt)

        # Final particle rotation
        self.rotation = degrees(theta + W*dt + g*dt)

    #----------------------------------------------------------------------------------------------
    #   Method to replace particles after rising up
    #----------------------------------------------------------------------------------------------
    def GetUpBackUp(self):
        self.x += rnd.gauss(0, 7)
        self.y += rnd.gauss(0, 7)
        self.rotation += rnd.gauss(0, 25)

    #----------------------------------------------------------------------------------------------
    #   Method which replaces particles after turning on the ground
    #----------------------------------------------------------------------------------------------
    def GetUpFrontUp(self):
        self.x += rnd.gauss(-30,7)*sin(radians(self.rotation))
        self.y += rnd.gauss(-30,7)*cos(radians(self.rotation))
        self.rotation += rnd.gauss(0, 25)
        self.GetUpBackUp()

    #----------------------------------------------------------------------------------------------
    #   Likelihood computation
    #----------------------------------------------------------------------------------------------
    def Sensor(self, Measures=None, weight=1):
        # Compute the angles the particle should be perceiving the landmark
        Blue = -degrees(atan2(-self.y, -self.x)) - self.rotation
        Red = -degrees(atan2(-self.y, 900-self.x)) - self.rotation
        Yellow = -degrees(atan2(600-self.y, -self.x)) - self.rotation
        Purple = -degrees(atan2(600-self.y, 900-self.x)) - self.rotation
        
        # Generate a vector with the measures
        M = [Blue, Red, Yellow, Purple]

        # Computes the cumulative likelihood of all particles.
        for i in range(4):
            if Measures[i] != -999:
                weight *= ComputeAngLikelihoodDeg(Measures[i], M[i], self.std[0])
        # Computes the likelihood given the IMU angle
        weight *= ComputeAngLikelihoodDeg(Measures[4], self.rotation, self.std[1])

        self.weight = weight
        return weight

#--------------------------------------------------------------------------------------------------
#   Computes the likelihood between two angles in degrees.
#--------------------------------------------------------------------------------------------------
def ComputeAngLikelihoodDeg(ang, base, std_deviation=0):
    # Note: the standard deviation also is in degrees

    # If the standard deviation is null
    if std_deviation == 0: 
        # return a binary answer.
        if ang == base:
            return 1
        else:
            return 0
    else:
        # else computes the cartesian points based on the angles,
        xa = cos(radians(ang))
        ya = sin(radians(ang))
        xb = cos(radians(base))
        yb = sin(radians(base))

        # computes the distance between these points,
        d = hypot(xa-xb, ya-yb)

        # converts the standard deviation into aa distance measure,
        sa = cos(radians(std_deviation))
        sb = sin(radians(std_deviation))
        s = hypot(sa-1, sb)

        # returns the likelihood between the given angles.
        return exp(-(d)/(2*s**2))/sqrt(2*pi*s**2)
