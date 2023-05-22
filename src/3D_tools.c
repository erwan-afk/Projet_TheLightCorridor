#include "3D_tools.h"
#include <iostream>

/* Camera parameters and functions */
float theta = 0.0f; // Angle between x axis and viewpoint
float phy = 90.0f; // Angle between z axis and viewpoint
float dist_zoom = 35.0f; // Distance between origin and viewpoint



void setCamera() {
	gluLookAt(dist_zoom,0.0,0.0, //origin cam
			  0.0,0.0,0.0, //point regardé
			  0.0,0.0,1.0);//orientation 
}

/* Convert degree to radians */
float toRad(float deg) {
	return deg*M_PI/180.0f;
}


void drawSquare(bool blend) {
	if (blend)
	{
		glBegin(GL_TRIANGLE_FAN);
	}else {
		glBegin(GL_LINE_LOOP);
	}
		glTexCoord2f(0, 0);
		glVertex3f(0.5,-0.5,0.0);
		glTexCoord2f(1, 0);
		glVertex3f(0.5,0.5,0.0);
		glTexCoord2f(1, 1);
		glVertex3f(-0.5,0.5,0.0);
		glTexCoord2f(0, 1);
		glVertex3f(-0.5,-0.5,0.0);

	glEnd();
}

void drawCube() {
	
	glPushMatrix(); // Sauvegarde de la matrice de transformation actuelle
	// Face avant (Z positif)
	glTranslatef(0.0, 0.0, 0.5); // Translation vers l'avant
	drawSquare(false); // Dessin de la face avant
	// Face arrière (Z négatif)
	glTranslatef(0.0, 0.0, -1.0); // Translation vers l'arrière
	drawSquare(false); // Dessin de la face arrière

	glRotatef(90.0, 1.0, 0.0, 0.0); // Rotation de 90 degrés autour de Y
	// Face avant (Z positif)
	glTranslatef(0.0, 0.5, 0.5); // Translation vers l'avant
	drawSquare(false); // Dessin de la face avant
	// Face arrière (Z négatif)
	glTranslatef(0.0, 0.0, -1.0); // Translation vers l'arrière
	drawSquare(false); // Dessin de la face arrière
	
	glPopMatrix(); // Restauration de la matrice de transformation précédente
}





void drawCircle() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,0.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawCone() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawPrism() {
    glBegin(GL_LINE_LOOP);

    // Face avant
    glVertex3f(0.0f, 0.5f, 0.0f);    // Sommet
    glVertex3f(-0.5f, -0.5f, 0.5f);  // Coin inférieur gauche
    glVertex3f(0.5f, -0.5f, 0.5f);   // Coin inférieur droit

    // Face droite
    glVertex3f(0.0f, 0.5f, 0.0f);    // Sommet
    glVertex3f(0.5f, -0.5f, 0.5f);   // Coin inférieur droit
    glVertex3f(0.5f, -0.5f, -0.5f);  // Coin inférieur gauche

    // Face arrière
    glVertex3f(0.0f, 0.5f, 0.0f);    // Sommet
    glVertex3f(0.5f, -0.5f, -0.5f);  // Coin inférieur gauche
    glVertex3f(-0.5f, -0.5f, -0.5f); // Coin inférieur droit

    // Face gauche
    glVertex3f(0.0f, 0.5f, 0.0f);    // Sommet
    glVertex3f(-0.5f, -0.5f, -0.5f); // Coin inférieur droit
    glVertex3f(-0.5f, -0.5f, 0.5f);  // Coin inférieur gauche

    // Base
    glVertex3f(-0.5f, -0.5f, 0.5f);  // Coin inférieur gauche de la face avant
    glVertex3f(0.5f, -0.5f, 0.5f);   // Coin inférieur droit de la face avant
    glVertex3f(0.5f, -0.5f, -0.5f);  // Coin inférieur droit de la face droite

    glVertex3f(-0.5f, -0.5f, 0.5f);  // Coin inférieur gauche de la face avant
    glVertex3f(0.5f, -0.5f, -0.5f);  // Coin inférieur droit de la face droite
    glVertex3f(-0.5f, -0.5f, -0.5f); // Coin inférieur gauche de la face arrière

    glEnd();
}



void drawSphere(GLuint texture) {
	GLUquadric* sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    glPushMatrix();
    gluSphere(sphere, 1.0f, 32, 32);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void getColor(float depth, float *color){
    float baseColor[3] = {0.0, 0.0, 1.0}; // Couleur de base
    float factor = depth/90.0; // Calcul du facteur de réduction de luminosité
		color[0] = 0.0f;
		color[1] = 0.0f;
        color[2] = (baseColor[2] * factor)+1;// Calcul de la couleur réduite
		//std::cout << color[2] << std::endl;
}