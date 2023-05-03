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

Ball myball = { 0.0f, 0.0f, 0.0f, 1.0f, 50.0f, 0.0f, 0.0f };

bool game_status = false;




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

void drawRaquette(double y, double z) {

        glPushMatrix();
        glColor3f(1.0,1.0,1.0); 
        glTranslatef(0.0,y,z);
        glRotatef(90.0,0.0,1.0,0.0); 
        glBegin(GL_LINE_LOOP);
            glVertex3f(xGraph+3.0,yGraph+3.0,0.0);
            glVertex3f(xGraph-3.0,yGraph+3.0,0.0);
            glVertex3f(xGraph-3.0,yGraph-3.0,0.0);
            glVertex3f(xGraph+3.0,yGraph-3.0,0.0);
        glEnd();
    glPopMatrix();

}

void drawBall(const Ball& ball,GLuint texture){

    glPushMatrix();
    glTranslatef(-ball.x,ball.y,ball.z);
    // if(ball.z < (hauteur/2) && ball.y < (largeur/2) && ball.z > -(hauteur/2) && ball.y > -(largeur/2)){
    //     glColor3f(1.0,0.0,0.0);
    // }else {
    //     glColor3f(0.0,1.0,0.0);
        
    // }
    
    drawSphere(texture);
    glPopMatrix();
}

void updateBall(Ball& ball, float deltaTime,float mouseY, float mouseZ) {
  // Met à jotrueur la position de la balle en fonction de sa vitesse
 // Prendre le temps écoulé en argument et mette à jour la position de la balle en fonction de celui-ci

    
    if (ball.z-ball.radius < -(hauteur/2) && ball.speedZ < 0 || ball.z+ball.radius > (hauteur/2) && ball.speedZ > 0){
        ball.speedZ = -ball.speedZ;
    }
     if ((ball.y-ball.radius < -(largeur/2) && ball.speedY < 0 ) || (ball.y+ball.radius > (largeur/2) && ball.speedY > 0)){
        ball.speedY = -ball.speedY;
    }
    if (ball.x+ball.radius > (profondeur) && ball.speedX > 0){
        ball.speedX = -ball.speedX;
    }
  


    float square_size = 6.0f;

    if (ball.x < (0.0f)){

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
            
      
            // sensY = 1;
            // sensZ = 1;

            ball.speedY = (ball.y - mouseY)*coefRaquette; 
            ball.speedZ = (ball.z - mouseZ)*coefRaquette; 
            
      
            std::cout << "speedY :"<< ball.speedY << "speedZ :" << ball.speedZ <<std::endl;
        }else{
            game_status = false;
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
    ball.x += ball.speedX * deltaTime;
    ball.y += ball.speedY * deltaTime;
    ball.z += ball.speedZ * deltaTime;

}


void stickyBall(Ball& ball,float mouseY, float mouseZ) {

    ball.x = 0.0f;
    ball.y = mouseY;
    ball.z = mouseZ;

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

Button button1 = {0.0f, 12.0f, 30.0f, 10.0f};
Button button2 = {0.0f, 0.0f, 30.0f, 10.0f};
Button button3 = {0.0f, -12.0f, 30.0f, 10.0f};



void drawButton(Button button) {
    glPushMatrix();
        glTranslatef(0.0f, button.y, button.z);
        glRotatef(90.0, 0.0, 1.0, 0.0); 
        glScalef(10.0f, 30.0f, 1.0f);
        drawSquare();
    glPopMatrix();
}

void drawMenu(GLuint texture1,GLuint texture2,GLuint texture3) {

    glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture1);
    drawButton(button1);

    glBindTexture(GL_TEXTURE_2D, texture2);
    drawButton(button2);

    glBindTexture(GL_TEXTURE_2D, texture3);
    drawButton(button3);

    glDisable(GL_TEXTURE_2D);
    
}

void drawScore(int score, GLuint* textures) {
    // Convertir le score en chaîne de caractères
    std::string score_str = std::to_string(score);

    // Calculer la position x, y et z du bouton
    float x = 0.0f;
    float y = -15.0f;
    float z = -15.0f;

    // Dessiner chaque chiffre de la chaîne de caractères
    for (int i = 0; i < score_str.size(); i++) {
        // Récupérer le chiffre en tant qu'entier
        int digit = score_str[i] - '0';

        // Dessiner le chiffre correspondant en utilisant la texture appropriée
		glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[digit]);
        glPushMatrix();
            glTranslatef(x, y, z);
            glRotatef(90.0, 0.0, 1.0, 0.0); 
            glScalef(4.0f, 2.5f, 1.0f);
            drawSquare();
        glPopMatrix();
		glDisable(GL_TEXTURE_2D);

        // Déplacer le curseur de dessin vers la droite pour le prochain chiffre
        y += 2.5f;
    }
}







    // Titre du menu
    /*
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.2f, 0.8f);
    const char* title = "Menu";
    for (int i = 0; i < strlen(title); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    
    // Bouton 1
    glColor3f(0.0f, 0.5f, 0.0f);
    glRectf(-0.2f, 0.2f, 0.2f, 0.4f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.1f, 0.3f);
    const char* button1 = "Option 1";
    for (int i = 0; i < strlen(button1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, button1[i]);
    }
    
    // Bouton 2
    glColor3f(0.5f, 0.0f, 0.0f);
    glRectf(-0.2f, -0.2f, 0.2f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.1f, -0.1f);
    const char* button2 = "Option 2";
    for (int i = 0; i < strlen(button2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, button2[i]);
    }
    */


