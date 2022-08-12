from screen import *

class SoccerField():
    def __init__(self, screen):
        self.screen = screen

    def draw_soccer_field(self):

        #background is green
        self.screen.background.fill((0,150,0))

        #field lines
        field_points = [(70,70),(520,70),(520,670),(970,670),(970,542),(910,542),(910,197),(970,197),(970,542),(970,70),(520,70),(520,670),(70,670),(70,542),(130,542),(130,197),(70,197),(70,542),(70,70)]
        pygame.draw.lines(self.screen.background,(255,255,255), False, field_points, 5)

        #areas
        pygame.draw.line(self.screen.background,(255,255,255),(245,370),(255,370), 7)
        pygame.draw.line(self.screen.background,(255,255,255),(250,365),(250,375), 7)

        #central circle
        pygame.draw.circle(self.screen.background,(255,255,255),(520,370),75,5)

        #penalty marks
        pygame.draw.line(self.screen.background,(255,255,255),(775,370),(785,370), 7)
        pygame.draw.line(self.screen.background,(255,255,255),(780,365),(780,375), 7)

        pygame.draw.line(self.screen.background,(255,255,255),(515,370),(525,370), 7)
        pygame.draw.line(self.screen.background,(255,255,255),(520,365),(520,375), 7)

        #goalsposts
        pygame.draw.circle(self.screen.background,(255,255,255),(70,280),10,0)
        pygame.draw.circle(self.screen.background,(255,255,255),(70,460),10,0)
        pygame.draw.circle(self.screen.background,(255,255,255),(970,280),10,0)
        pygame.draw.circle(self.screen.background,(255,255,255),(970,460),10,0)

        #landmarks
        # pygame.draw.circle(self.screen.background,(0,200,200),(70,70),7,0)
        # pygame.draw.circle(self.screen.background,(255,90,80),(970,70),7,0)
        # pygame.draw.circle(self.screen.background,(255,255,0),(70,670),7,0)
        # pygame.draw.circle(self.screen.background,(210,0,240),(970,670),7,0)
        


