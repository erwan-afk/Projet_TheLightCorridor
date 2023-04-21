#pragma once
#ifndef DRAW_SCENE_H
#define DRAW_SCENE_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

typedef struct Ball{
    float x;          // position en x
    float y;
    float z;           // position en y
    float radius;     // rayon de la balle
    float speedX;     // vitesse en x
    float speedY;     // vitesse en y
    float speedZ;     // vitesse en z
} Ball;

typedef struct Mur{
    float x;          
    float y;
    float z;

    float hauteur;
    float profondeur;

   
    string axe; 
    float orientation;
} Mur;

typedef struct vect{
    float x; 
    float y; 
    float z; 
}vect; 



void drawTunnel_base();
void drawRaquette(double x, double z);
void drawBall(const Ball& ball);
void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ);
void drawMur(Mur mur);
void drawTunnel(Mur tunnel[]);

extern Ball myball;  // Déclare l'instance myBall de la structure Ball
extern Mur mur;  // Déclare l'instance mur de la structure Mur
extern Mur tunnel[]; // Déclare l'instance tunnel[] de la structure Mur
extern bool game_status;
#endif
