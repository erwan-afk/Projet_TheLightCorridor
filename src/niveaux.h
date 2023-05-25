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
    
}Panneau;

typedef struct Bonus{
    float x;          
    float y;
    float z;

    int forme;
    int SpeedRotation;
    int angle;
    float taille;
    
}Bonus;

typedef struct Obstacle{
    vector<Panneau> Panneaux;
}Obstacle;


typedef struct Niveau{
    vector<Obstacle> Obstacles;
    vector<Bonus> Bonus;
}Niveau; 

extern std::vector<Niveau> Niveaux_tab;
extern Niveau niveau1;
extern Niveau niveau2;
extern Niveau niveau3;



