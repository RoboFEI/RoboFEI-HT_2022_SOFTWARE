import random as rnd

class Part(object):
    """docstring for Part"""
    def __init__(self):
        self.x = rnd.randint(0, 900)
        self.y = rnd.randint(0, 600)
        self.rotation = rnd.randint(-180, 180)
        # self.x = rnd.gauss(450, 10)
        # self.y = rnd.gauss(300, 10)
        # self.rotation = 90