
#include "draw_scene.h"
#include "3D_tools.h"

#include <iostream>

float profondeur = 90.0;
float hauteur = 20.0;
float largeur = 30.0;

const float coefRaquette = 2.0; 

//Parametre souris 
float xGraph = 0.0;
float yGraph = 0.0; 

Ball myball = { 0.0f, 0.0f, 0.0f, 0.5f, 50.0f, 0.0f };
int sens = 1;

void drawTunnel() {
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
            glVertex3f(xGraph+2.0,yGraph+2.0,0.0);
            glVertex3f(xGraph-2.0,yGraph+2.0,0.0);
            glVertex3f(xGraph-2.0,yGraph-2.0,0.0);
            glVertex3f(xGraph+2.0,yGraph-2.0,0.0);
        glEnd();
    glPopMatrix();

}

void drawBall(const Ball& ball){

    glPushMatrix();
    glTranslatef(-ball.x,ball.y,ball.z);
    glColor3f(1.0,0.0,0.0);
    drawSphere();
    glPopMatrix();
}

void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ) {
  // Met à jour la position de la balle en fonction de sa vitesse
 // Prendre le temps écoulé en argument et mette à jour la position de la balle en fonction de celui-ci
    

    if (ball.x > profondeur){
        sens = 0;
        ball.speedY = -ball.speedY; 
        ball.speedZ = -ball.speedZ;

    }
    if (ball.z > hauteur/2){
        ball.speedZ = -ball.speedZ;
    }
    if (ball.z < -hauteur/2){
        ball.speedZ = -ball.speedZ;
    }
    if (ball.y > largeur/2){
        ball.speedY = -ball.speedY; 
    }
    if (ball.y < -largeur/2){
        ball.speedY = -ball.speedY; 
    }


    float square_size = 4.0f;

    if (ball.x < 0.0f + ball.radius){
        
        if (ball.y >= (mouseZ - square_size/2.0f) and 
        ball.y <= (mouseZ + square_size/2.0f) and
        ball.z >= (mouseY - square_size/2.0f) and 
        ball.z <= (mouseY + square_size/2.0f)) {

            //float distance = sqrt(pow((mouseZ - ball.y),2) + pow((mouseY - ball.z),2));
            //float distance_x = ball.x - (mouseY + square_size/2.0f);
            //float distance_y = ball.y - (mouseZ + square_size/2.0f);
            
            
            sens = 1;
    

            ball.speedY = (ball.y - mouseY)*coefRaquette; 
            ball.speedZ = (ball.z - mouseZ)*coefRaquette; 
      
            std::cout << "speedY :"<< ball.speedY << "speedZ :" << ball.speedZ <<std::endl;
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

    if (sens == 1)
    {
        ball.x+=ball.speedX* deltaTime;
        ball.y+=ball.speedY* deltaTime;
        ball.z+=ball.speedZ* deltaTime;
    }else
    {
        ball.x-=ball.speedX* deltaTime;
        ball.y-=ball.speedY* deltaTime;
        ball.z-=ball.speedZ* deltaTime;
    }
  
}

Mur mur = {-40.0,0.0,0.0,6.0,6.0};

void drawMur(Mur mur) {

    glPushMatrix();
        glColor3f(0.0,1.0,0.0); 
        glTranslatef(mur.x,mur.y,mur.z);
        glRotatef(90.0,0.0,1.0,0.0); 
        glBegin(GL_POLYGON);
            glVertex3f(xGraph+mur.largeur,yGraph+mur.largeur,0.0);
            glVertex3f(xGraph-mur.largeur,yGraph+mur.largeur,0.0);
            glVertex3f(xGraph-mur.largeur,yGraph-mur.largeur,0.0);
            glVertex3f(xGraph+mur.largeur,yGraph-mur.largeur,0.0);
        glEnd();
    glPopMatrix();

}