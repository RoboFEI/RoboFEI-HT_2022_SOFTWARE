__author__ = "RoboFEI-HT"
__authors__ = "Aislan C. Almeida"
__license__ = "GNU General Public License v3.0"

from world import *
from simulation import *
from part import *

def main():

    screen = Screen()

    simul = Simulation(screen)

    field = SoccerField(screen)

    simul.field = field

    parts = []

    for i in range(1000):
        parts.append(Part())

    simul.particles = parts

    #Main loop
    while True:

        #Process events
        simul.perform_events()

         #update soccer field
        field.draw_soccer_field()

        #Draw robots, ball and update the current frame
        simul.display_update()

        #Pause for the next frame
        screen.clock.tick(60)

#Call the main function, start up the simulation
if __name__ == "__main__":
    main()
