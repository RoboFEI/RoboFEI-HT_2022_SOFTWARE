__author__ = "RoboFEI-HT"
__authors__ = "Aislan C. Almeida"
__license__ = "GNU General Public License v3.0"

from Viewer import *
from particle import *
from multiprocessing import Pool 

def main():

    pool = Pool()

    screen = Screen()

    simul = Simulation(screen)

    field = SoccerField(screen)

    simul.field = field

    parts = []

    for i in range(10000):
        parts.append(Particle(450, 300, 0))
        # parts[i].a = (0.005, 5, 0.00005, 0.05, 0.00005, 0.05)

    simul.particles = parts

    #Main loop
    while True:

        #Process events
        simul.perform_events()

        for i in range(10000/4):
            pool.map(parts[i*4].Motion(), (100, 90, 1.0/60))
            pool.map(parts[i*4+1].Motion(), (100, 90, 1.0/60))
            pool.map(parts[i*4+2].Motion(), (100, 90, 1.0/60))
            pool.map(parts[i*4+3].Motion(), (100, 90, 1.0/60))
        # for part in parts:
        #     part.Motion(100, 90, 1.0/60)

         #update soccer field
        field.draw_soccer_field()

        #Draw robots, ball and update the current frame
        simul.display_update()

        #Pause for the next frame
        screen.clock.tick(60)

#Call the main function, start up the simulation
if __name__ == "__main__":
    main()
