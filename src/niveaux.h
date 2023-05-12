#pragma once
#include "draw_scene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct Panneau{
    float x;          
    float y;
    float z;

    
    float hauteur; 
    float largeur; 

    bool impact;
    
};

typedef struct Bonus{
    float x;          
    float y;
    float z;

    int forme;
    int SpeedRotation;
    int angle;
    
};

typedef struct Obstacle{
    vector<Panneau> Panneaux;
};


struct Niveau{
    int id; 
    vector<Obstacle> Obstacles;
    vector<Bonus> Bonus;
}; 

extern Niveau niveau1;



