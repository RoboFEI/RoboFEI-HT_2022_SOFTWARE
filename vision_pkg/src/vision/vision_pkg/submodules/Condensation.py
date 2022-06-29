# -*- coding: UTF8 -*-

#\--------------------------------------------------------------------------\
#\ Condensation Algorithm 
#\--------------------------------------------------------------------------\

import random
import numpy as np
from scipy import stats
import time
import cv2
import math

class Image:
    def __init__(self):
		# Inicia a Captura
        self.capture = cv2.VideoCapture(0)
		# Seta o tamanho da captura
        self.capture.set(3,1920) #720 1280 1920
        self.capture.set(4,1080) #480 720 1080
		# Pega um frame da captura
        self.ret , self.image = self.capture.read()
		#Pega as dimensões da imagem
        height, width, channels = self.image.shape
		# Mostra o quadro da imagem
        cv2.imshow("Capture",self.image)
		#Define o tamanho da imagem
        self.size = (width,height)


    def getColor(self,part):
        # O valor de coordenadas é convertido para int
        x = part[0]
        y = part[1]
        #Se as partículas sairem para fora da tela
        if((x<0 or x>self.size[0]) or (y<0 or y>self.size[1])):
            return((0,0,0,0))
        else:
            return(self.image[int(part[1]),int(part[0])])

    def create(self):
		# Guarda um frame para usar
        _, self.image = self.capture.read()


##########################################################
class SystemModel:
    def __init__(self,model):
        self.model = model
    def generate(self,part,w):
        return(self.model(part,w))
###########################################################
class Likelihood:
    def __init__(self,model):
        self.model = model

    def generate(self,part,mv):
        return(self.model(part,mv))

    def normalization(self,particles,mv):
        return(sum([self.generate(part,mv) for part in particles]))
###########################################################
def model_movement(part,w):
    #Modelo de Movimento Constante
    #Vetor de estado assume (x, y, vx, vy)
    F = np.matrix([ [1,0,1,0],
                    [0,1,0,1],
                    [0,0,1,0],
                    [0,0,0,1] ])

    return(np.array(np.dot(F,part))[0]+w)
###########################################################
def model_likelihood(part,mv):
    #Adquire informação de cor de um ponto que corresponde ao movimento mv das coordenadas a partir de part
    mv_color = img.getColor(part)
    mv_color = mv_color[0:3]
#   target_color = (150,90,40) BGR
    target_color = (255,255,255)


    #Modelo Gaussiano para a diferença de probabilidade de cor
    delta = np.array(mv_color)-np.array(target_color)
    dist_sqr = sum(delta*delta)
    sigma = 10000.0
    gauss = np.exp(-0.5*dist_sqr/(sigma*sigma)) / (np.sqrt(2*np.pi)*sigma)
    return(gauss)


##########################################################
def resampling(particles,weights):
    N = len(particles)

    #Ordenar as partículas na ordem de peso decrescente
    sorted_particle = sorted([list(x) for x in zip(particles,weights)],key=lambda x:x[1],reverse=True)

    #Reamostragem a partícula de acordo com os pesos
    resampled_particles = []

    Beta = 0.0
    while(len(resampled_particles)<N):
        for sp in sorted_particle:
#              print(sp[1])
#              if sp[1] > Beta:
#                  Beta = sp[1]
              resampled_particles += [sp[0]]
              resampled_particles += [sp[0]]
              resampled_particles += [sp[0]]
              resampled_particles += [sp[0]]
    resampled_particles = resampled_particles[0:N]

    return(resampled_particles)

##########################################################
def filtration(particles,mv,systemModel,likelihood):
    #Gerando um número aleatório
    dim = len(particles[1])
    N = len(particles)
    sigma = 3.0 #Escala?
    rnorm = stats.norm.rvs(0,sigma,size=N*dim)
    ranges = zip([N*i for i in range(dim)],[N*i for i in (range(dim+1)[1:])])
    ws = np.array([rnorm[p:q] for p,q in ranges])
    ws = ws.transpose()

    #Gera uma amostra de predição
    particles_predict = [systemModel.generate(part,w) for part,w in zip(particles,ws)]
    
    #Calcula os pesos de probabilidade
    normalization_factor = likelihood.normalization(particles_predict,mv)
    likelihood_weights = [likelihood.generate(part,mv)/normalization_factor for part in particles_predict]
    #Reamostragem pelos pesos
    particles_resampled = resampling(particles_predict,likelihood_weights)
    return(particles_resampled)

###########################################################
#Para gerar as partículas iniciais. Modelo suposição (x, y, vx, vy)
def initiate_particles(Size,sampleSize):
    s=math.floor(sampleSize)
    size=int(s)
    xs = [random.uniform(0,Size[0]) for i in range(size)]
    ys = [random.uniform(0,Size[1]) for i in range(size)]
    vxs = [random.uniform(0,5) for i in range(size)]
    vys = [random.uniform(0,5) for i in range(size)]

    return([list(s) for s in zip(xs,ys,vxs,vys)])

##########################################################
#Para exibir uma imagem com uma partícula
def showImage(particles,img):
    #Clona a imagem para o desenho de partícula
    dst = img.copy()

    #Desenhando uma partícula
    for part in particles:
#        print (part)
        cv2.circle(dst,(int(part[0]),int(part[1])),3, (0,0,255))


    #Precisa girar en torno do eixo y flipmode =1, pois o 
    #sistema de coordenadas é diferente de part e a imagem de destino.
    cv2.flip(dst,1)
    cv2.imshow("Capture",dst)


############################################################
if(__name__=="__main__"):
    #Especifique a origem da imagem
    img = Image()
   
    #Especificar o número de partículas
    Particles_Number = 2000
    #Gerando o modelo
    systemModel = SystemModel(model_movement)
    likelihood = Likelihood(model_likelihood)
    #Inicicalizando as particulas
    particles = initiate_particles(img.size,Particles_Number)
#    print("Passou : ", particles)
    while(True):

        showImage(particles, img.image)
#        print("Passou")
        img.create()

        particles = filtration(particles,img,systemModel,likelihood)
        if cv2.waitKey(1)&0xFF == ord('q'):
            break

