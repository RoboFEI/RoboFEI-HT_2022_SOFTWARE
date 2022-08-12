#! /usr/bin/env python
#coding: utf-8


__author__ = "RoboFEI-HT"
__authors__ = "Danilo H. Perico"


###discretization of the orientation following OPRA6
def opra_discretization(vision_delta_orient):
    if vision_delta_orient == 0:
       qualitative_region = 0
    ###left (-)
    elif vision_delta_orient  > 0 and vision_delta_orient < 30:
        qualitative_region = 1
    elif vision_delta_orient == 30:
        qualitative_region = 2
    elif vision_delta_orient  > 30 and vision_delta_orient < 60:
        qualitative_region = 3
    elif vision_delta_orient  == 60:
        qualitative_region = 4
    elif vision_delta_orient  > 60 and vision_delta_orient < 90:
        qualitative_region = 5
    elif vision_delta_orient  == 90:
        qualitative_region = 6
    elif vision_delta_orient  > 90 and vision_delta_orient < 120:
        qualitative_region = 7
    elif vision_delta_orient  == 120:
        qualitative_region = 8
    elif vision_delta_orient  > 120 and vision_delta_orient > 150:
        qualitative_region = 9
    elif vision_delta_orient  == 150:
        qualitative_region = 10
    elif vision_delta_orient  > 150 and vision_delta_orient > 180:
        qualitative_region = 11
    elif vision_delta_orient  == 180:
        qualitative_region = 12
    ###right (+)
    elif vision_delta_orient  < 0 and vision_delta_orient > -30:
        qualitative_region = 23
    elif vision_delta_orient  == -30:
        qualitative_region = 22
    elif vision_delta_orient  < -30 and vision_delta_orient > -60:
        qualitative_region = 21
    elif vision_delta_orient  == -60:
        qualitative_region = 20
    elif vision_delta_orient  < -60 and vision_delta_orient > -90:
        qualitative_region = 19
    elif vision_delta_orient  == -90:
        qualitative_region = 18
    elif vision_delta_orient  < -90 and vision_delta_orient > -120:
        qualitative_region = 17
    elif vision_delta_orient  == -120:
        qualitative_region = 16
    elif vision_delta_orient  < -120 and vision_delta_orient > -150:
        qualitative_region = 15
    elif vision_delta_orient  == -150:
        qualitative_region = 14
    elif vision_delta_orient  < -150 and vision_delta_orient > -180:
        qualitative_region = 13
    return qualitative_region


###discretization of the distance following the elevated point concept with m = 6
def distance_discretization(dist):
    delta = 1
    qualitative_dist = 0.0
    dist = dist / 100
    if dist < 0.33*delta:
       qualitative_dist = 1
    elif dist == 0.33*delta:
        qualitative_dist = 2
    elif dist > 0.33*delta and dist < 0.66*delta:
        qualitative_dist = 3
    elif dist == 0.66*delta:
        qualitative_dist = 4
    elif dist > 0.66*delta and dist < 1*delta:
        qualitative_dist = 5
    elif dist == 1*delta:
        qualitative_dist = 6
    elif dist > 1*delta and dist < 1.5*delta:
        qualitative_dist = 7
    elif dist == 1.5*delta:
        qualitative_dist = 8
    elif dist > 1.5*delta and dist < 3*delta:
        qualitative_dist = 9
    elif dist == 3*delta:
        qualitative_dist = 10
    elif dist > 3*delta:
        qualitative_dist = 11
    return qualitative_dist
