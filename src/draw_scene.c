#include "draw_scene.h"
#include "3D_tools.h"

#include <iostream>

float profondeur = 90.0;
float hauteur = 20.0;
float largeur = 30.0;

const float coefRaquette = 5.0; 

//Parametre souris 
float xGraph = 0.0;
float yGraph = 0.0; 

<<<<<<< HEAD
Ball myball = { 0.0f, 0.0f, 0.0f, 0.3f, 50.0f, 0.0f };
int sensX = 1;
int sensY = 1;
int sensZ = 1;

bool game_status = true;
=======
Ball myball = { 0.0f, 0.0f, 0.0f, 1.0f, 50.0f, 0.0f, 0.0f };

bool game_status = false;

>>>>>>> main

void drawTunnel_base() {
    glPushMatrix();
        glTranslatef(-profondeur/2,0.0,-(hauteur/2));
        glPushMatrix();
            glTranslatef(0.0,0.0,0.0);
            glScalef(profondeur,largeur,1.0);
            glColor3f(0.0,0.0,0.5);
            drawSquare();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,0.0,hauteur);
            glScalef(profondeur,largeur,1.0);
            glColor3f(0.0,0.0,0.5);
            drawSquare();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,largeur/2,hauteur/2.0);
            glRotatef(90,1.0,0.0,0.0);
            glScalef(profondeur,hauteur,1.0);
            glColor3f(0.0,0.0,0.9);
            drawSquare();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,-largeur/2,hauteur/2.0);
            glRotatef(90,1.0,0.0,0.0);
            glScalef(profondeur,hauteur,1.0);
            glColor3f(0.0,0.0,0.9);
            drawSquare();
        glPopMatrix();
    glPopMatrix();
}

void drawRaquette(double x, double z) {
    glPushMatrix();
        glColor3f(1.0,1.0,1.0); 
        glTranslatef(0.0,x,z);
        glRotatef(90.0,0.0,1.0,0.0); 
        glBegin(GL_LINE_LOOP);
            glVertex3f(xGraph+3.0,yGraph+3.0,0.0);
            glVertex3f(xGraph-3.0,yGraph+3.0,0.0);
            glVertex3f(xGraph-3.0,yGraph-3.0,0.0);
            glVertex3f(xGraph+3.0,yGraph-3.0,0.0);
        glEnd();
    glPopMatrix();

}

void drawBall(const Ball& ball){

    glPushMatrix();
    glTranslatef(-ball.x,ball.y,ball.z);
    if(ball.z < -(hauteur/2)|| ball.y < -(largeur/2)){
        glColor3f(0.0,1.0,0.0);
    }else {
        glColor3f(1.0,0.0,0.0);
    }
    drawSphere();
    glPopMatrix();
}

void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ) {
  // Met à jotrueur la position de la balle en fonction de sa vitesse
 // Prendre le temps écoulé en argument et mette à jour la position de la balle en fonction de celui-ci
<<<<<<< HEAD
    

    if (ball.x+3.0f > profondeur){
        ball.x = ball.x - 3.0f;
        sensX = 0;
        
    }
    if (ball.z+3.0f > hauteur/2){
        sensZ = 0; 
    }
    if (ball.z+3.0f < -hauteur/2){
        sensZ = 1;
    }
    if (ball.y+3.0f > largeur/2){
        sensY = 0;
    }
    if (ball.y+3.0f < -largeur/2){
        sensY = 1;
=======

    
    if (ball.z-ball.radius < -(hauteur/2) && ball.speedZ < 0 || ball.z+ball.radius > (hauteur/2) && ball.speedZ > 0){
        ball.speedZ = -ball.speedZ;
    }
     if ((ball.y-ball.radius < -(largeur/2) && ball.speedY < 0 ) || (ball.y+ball.radius > (largeur/2) && ball.speedY > 0)){
        ball.speedY = -ball.speedY;
    }
    if (ball.x+ball.radius > (profondeur) && ball.speedX > 0){
        ball.speedX = -ball.speedX;
>>>>>>> main
    }
  


    float square_size = 6.0f;

<<<<<<< HEAD
    float square_size = 6.0f;

    if (ball.x < (0.0f + 3.0f)){

=======
    if (ball.x < (0.0f)){

>>>>>>> main
    std::cout << "y:"<< mouseY << std::endl;
    std::cout << "z:"<< mouseZ << std::endl;

    std::cout << "y_ball:"<< ball.y << std::endl;
    std::cout << "z_ball::"<< ball.z << std::endl;
        
        if (ball.y >= (mouseY - square_size/2.0f) and 
        ball.y <= (mouseY + square_size/2.0f) and
        ball.z >= (mouseZ - square_size/2.0f) and 
        ball.z <= (mouseZ + square_size/2.0f)) {

            //float distance = sqrt(pow((mouseZ - ball.y),2) + pow((mouseY - ball.z),2));
            //float distance_x = ball.x - (mouseY + square_size/2.0f);
            //float distance_y = ball.y - (mouseZ + square_size/2.0f);
            if (ball.x-ball.radius < (0) && ball.speedX < 0  ){
                ball.speedX = -ball.speedX;
            }
            
<<<<<<< HEAD
            
            sensX = 1;
=======
      
>>>>>>> main
            // sensY = 1;
            // sensZ = 1;

            ball.speedY = (ball.y - mouseY)*coefRaquette; 
            ball.speedZ = (ball.z - mouseZ)*coefRaquette; 
            
      
            std::cout << "speedY :"<< ball.speedY << "speedZ :" << ball.speedZ <<std::endl;
        }else{
            game_status = false;
<<<<<<< HEAD
=======

>>>>>>> main
        }
        /*
        if (ball.y >= mouseY && ball.y <= mouseY + 2.0f && ball.z >= mouseZ && ball.z <= mouseZ + 2.0f) {
            // La balle est sur le carré, elle rebondit
            sens = 1;
            std::cout << "carre:" << mouseY + 4.0f << "," << mouseZ + 4.0f <<std::endl;
            std::cout << "balle:" << ball.y << "," << ball.z <<std::endl;
        }
        */
        //sens = 1;
    }
<<<<<<< HEAD
    

    if (sensX == 1)
    {
        ball.x+=ball.speedX* deltaTime;
    }else
    {
        ball.x-=ball.speedX* deltaTime;
    }

    if (sensY == 1)
    {
        ball.y+=ball.speedY* deltaTime;
    }else
    {
        ball.y-=ball.speedY* deltaTime;
    }

    if (sensZ == 1)
    {
        ball.z+=ball.speedZ* deltaTime;
    }else
    {
        ball.z-=ball.speedZ* deltaTime;
    }

    


=======
    ball.x += ball.speedX * deltaTime;
    ball.y += ball.speedY * deltaTime;
    ball.z += ball.speedZ * deltaTime;
    


>>>>>>> main
}

//Mur mur = {-profondeur/2,0.0,-(hauteur/2),largeur,0.0,profondeur,"x",0.0};
//Mur mur = {-profondeur/2,0.0,(hauteur/2),largeur,0.0,profondeur,"x",0.0};

//Mur mur = {-profondeur/2,0.0,(hauteur/2),largeur,profondeur,"x",0.0};
//Mur mur = {-profondeur/2,0.0,-(hauteur/2),largeur,profondeur,"x",0.0};
//Mur mur = {-profondeur/2.0f,(largeur/2.0f),0.0,hauteur,profondeur,"x",90.0};
Mur mur = {-profondeur/2.0f,0.0,0.0,6.0,6.0,"y",90.0};

Mur tunnel[] = {
    
    {-profondeur/2,0.0,(hauteur/2),largeur,profondeur,"x",0.0},
    {-profondeur/2.0f,-(largeur/2.0f),0.0,hauteur,profondeur,"x",90.0},
    {-profondeur/2,0.0,-(hauteur/2),largeur,profondeur,"x",0.0},
    {-profondeur/2.0f,(largeur/2.0f),0.0,hauteur,profondeur,"x",90.0},
    
};

void drawMur(Mur mur) {

    glPushMatrix();
        
        glTranslatef(mur.x,mur.y,mur.z);

        if (mur.axe == "x") {
            glRotatef(mur.orientation, 1.0, 0.0, 0.0);
        } else if (mur.axe == "y") {
            glRotatef(mur.orientation, 0.0, 1.0, 0.0);
        } else if (mur.axe == "z") {
            glRotatef(mur.orientation, 0.0, 0.0, 1.0);
        }
        //glScalef(mur.largeur,mur.hauteur,1.0);
        glScalef(mur.profondeur,mur.hauteur,1.0);
        
        
        drawSquare();
        
    glPopMatrix();

}

void drawTunnel(Mur tunnel[]) {

    for (int i = 0; i < 4; i++)
    {   
        if (i%2 ==0)
        {
            glColor3f(0.0,0.0,0.5);
        }else
        {
            glColor3f(0.0,0.0,0.9);
        }
        drawMur(tunnel[i]);
    }
    
}

/*
        glPushMatrix();
            glTranslatef(0.0,largeur/2,hauteur/2.0);
            glRotatef(90,1.0,0.0,0.0);
            glScalef(profondeur,hauteur,1.0);
            glColor3f(0.0,0.0,0.9);
            drawSquare();
        glPopMatrix();
<<<<<<< HEAD
*/
=======
*/


>>>>>>> main
