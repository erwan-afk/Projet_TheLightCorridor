#pragma once
#ifndef DRAW_SCENE_H
#define DRAW_SCENE_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    float dimension;
    int side;
} Mur;

void drawTunnel();
void drawRaquette(double x, double z);
void drawBall(const Ball& ball);
void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ);

extern Ball myball;  // Déclare l'instance myBall de la structure Ball

#endif

