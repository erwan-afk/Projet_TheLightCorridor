#pragma once

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

    float orientation;
} Mur;

struct Button {
    float y;     // position y
    float z;     // position z
    float width; // largeur
    float height;// hauteur
};

struct Line {
    float profondeur;
};

void drawRaquette(double y, double z);
void drawBall(const Ball& ball,GLuint texture);
void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ);
void drawTunnel(Mur tunnel[],GLuint texture);
void stickyBall(Ball& ball,float mouseY, float mouseZ);
void drawButton(Button button);
void drawMenu(GLuint texture1,GLuint texture2,GLuint texture3);
void drawScore(int score, GLuint* textures);
void drawLives(int lives,GLuint texture);
void drawCorridor(float deltaTime); 
void drawPrism();
void check_dead(Ball& ball);


extern Ball myball;  // Déclare l'instance myBall de la structure Ball
extern Mur mur;  // Déclare l'instance mur de la structure Mur
extern Mur tunnel[]; // Déclare l'instance tunnel[] de la structure Mur
extern bool game_status;
extern float raquette_radius;

extern Button button1;
extern Button button2;
extern Button button3;

extern float profondeur;
extern float hauteur;
extern float largeur;

extern float positionJoueur;
extern bool run;
