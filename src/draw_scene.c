#include "draw_scene.h"
#include "3D_tools.h"

float profondeur = 90.0;
float hauteur = 20.0;

void drawTunnel() {
		glTranslatef(0.0,0.0,-(hauteur/2));

        glPushMatrix();
		    glTranslatef(0.0,0.0,0.0);
		    glScalef(profondeur,30,1.0);
		    glColor3f(0.0,0.0,0.5);
		    drawSquare();
		glPopMatrix();

        glPushMatrix();
		    glTranslatef(0.0,0.0,hauteur);
		    glScalef(profondeur,30.0,1.0);
		    glColor3f(0.0,0.0,0.5);
		    drawSquare();
		glPopMatrix();

        glPushMatrix();
		    glTranslatef(0.0,15.0,hauteur/2.0);
			glRotatef(90,1.0,0.0,0.0);
		    glScalef(profondeur,hauteur,1.0);
		    glColor3f(0.0,0.0,0.9);
		    drawSquare();
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(0.0,-15.0,hauteur/2.0);
			glRotatef(90,1.0,0.0,0.0);
		    glScalef(profondeur,hauteur,1.0);
		    glColor3f(0.0,0.0,0.9);
		    drawSquare();
		glPopMatrix();
}


