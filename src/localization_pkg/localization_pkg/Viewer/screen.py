import pygame

class Screen():
    def __init__(self, graphs):
        if graphs:
            self.screen_width = 1040
            self.screen_height = 740
            self.background = pygame.display.set_mode((self.screen_width, self.screen_height))
            print ('Localization Graphical Viewer')
            pygame.display.set_caption('Localization Graphical Viewer')
        else:
            print ('Localization Running')

        self.clock = pygame.time.Clock()
        pygame.init()
            
