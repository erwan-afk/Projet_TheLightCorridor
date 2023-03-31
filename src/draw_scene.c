
#include "draw_scene.h"
#include "3D_tools.h"

float profondeur = 90.0;
float hauteur = 20.0;
float largeur = 30.0;

//Para souris 
float xGraph = 0.0;
float yGraph = 0.0; 


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

void drawRaquette(){

    glPushMatrix();
        glColor3f(1.0,1.0,1.0); 
        glTranslatef(0.0,0.0,0.0);
        glRotatef(90.0,0.0,1.0,0.0); 
        glBegin(GL_LINE_LOOP);
            glVertex3f(xGraph+2.0,yGraph+2.0,0.0);
            glVertex3f(xGraph-2.0,yGraph+2.0,0.0);
            glVertex3f(xGraph-2.0,yGraph-2.0,0.0);
            glVertex3f(xGraph+2.0,yGraph-2.0,0.0);
        glEnd();
    glPopMatrix();

}