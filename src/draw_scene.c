#include "draw_scene.h"
#include "3D_tools.h"

void drawTunnel() {
        glPushMatrix();
		    glTranslatef(0.0,0.0,0.0);
		    glScalef(30.0,30.0,1.0);
		    glColor3f(0.0,0.0,0.1);
		    drawSquare();
		glPopMatrix();

        glPushMatrix();
		    glTranslatef(0.0,0.0,10.0);
		    glScalef(30.0,30.0,1.0);
		    glColor3f(0.0,0.0,0.1);
		    drawSquare();
		glPopMatrix();

        glPushMatrix();
		    glTranslatef(0.0,0.0,10.0);
		    glScalef(30.0,10.0,1.0);
		    glColor3f(0.0,0.0,0.1);
		    drawSquare();
		glPopMatrix();
}


