    #include "config.h"
    #include "draw_scene.h"
    #include "3D_tools.h"
    #include "niveaux.h"



    #include <vector>
    #include <iostream>

    float profondeur = 180.0;
    float hauteur = 20.0;
    float largeur = 30.0;

    const float coefRaquette = 5.0; 

    //Parametre souris 
    float xGraph = 0.0;
    float yGraph = 0.0; 

    Ball myball = { 0.0f, 0.0f, 0.0f, 1.0f, 50.0f, 0.0f, 0.0f };

    bool game_status = false;

    float raquette_radius = 3.0f;

    bool run = false;
    float espaceObstacle = 10.0f;
    float positionJoueur = 0.0f;
    float vitesse_joueur = 30.0f;


    void drawRaquette(double y, double z) {

            glPushMatrix();
            glColor3f(1.0,1.0,1.0); 
            glTranslatef(0.0,y,z);
            glRotatef(90.0,0.0,1.0,0.0); 
            glBegin(GL_LINE_LOOP);
                glVertex3f(xGraph+raquette_radius,yGraph+raquette_radius,0.0);
                glVertex3f(xGraph-raquette_radius,yGraph+raquette_radius,0.0);
                glVertex3f(xGraph-raquette_radius,yGraph-raquette_radius,0.0);
                glVertex3f(xGraph+raquette_radius,yGraph-raquette_radius,0.0);
            glEnd();
        glPopMatrix();

    }

    void drawBall(const Ball& ball,GLuint texture){

        glPushMatrix();
        glTranslatef(-ball.x,ball.y,ball.z);
        glRotatef(-90,1.0,0.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        glScalef(1.3,1.3,1.3);
        drawSphere(texture);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0,0.0,0.0);
        glTranslatef(-ball.x-2,ball.y,-hauteur/2+0.1);
        glScalef(abs((ball.z-hauteur/2)/hauteur)+1,abs((ball.z-hauteur/2)/hauteur)+1,abs((ball.z-hauteur/2)/hauteur)+1);
        drawCircle();
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



    for (int i = 0; i < config.active_niveau.Obstacles.size(); i++)
    {
        for (int j = 0; j < config.active_niveau.Obstacles[i].Panneaux.size(); j++)
        {
            if (ball.y + ball.radius >= (config.active_niveau.Obstacles[i].Panneaux[j].y - config.active_niveau.Obstacles[i].Panneaux[j].hauteur/2.0f) and
                ball.y - ball.radius<= (config.active_niveau.Obstacles[i].Panneaux[j].y + config.active_niveau.Obstacles[i].Panneaux[j].hauteur/2.0f) and
                ball.z + ball.radius >= (config.active_niveau.Obstacles[i].Panneaux[j].z - config.active_niveau.Obstacles[i].Panneaux[j].largeur/2.0f) and 
                ball.z - ball.radius<= (config.active_niveau.Obstacles[i].Panneaux[j].z + config.active_niveau.Obstacles[i].Panneaux[j].largeur/2.0f))
            {   
                //std::cout << ball.speedX << endl;
                if (ball.x + ball.radius >= -config.active_niveau.Obstacles[i].Panneaux[j].x - config.active_niveau.Obstacles[i].Panneaux[j].largeur / 2.0f && 
                    ball.x - ball.radius <= -config.active_niveau.Obstacles[i].Panneaux[j].x + config.active_niveau.Obstacles[i].Panneaux[j].largeur / 2.0f && ball.speedX > 0) {
                    ball.speedX = -ball.speedX;
                    ball.x = ball.x-1.0;
                    

                    config.active_niveau.Obstacles[i].Panneaux[j].impact = true;
                

                }

                else if (ball.x + ball.radius >= -config.active_niveau.Obstacles[i].Panneaux[j].x - config.active_niveau.Obstacles[i].Panneaux[j].largeur / 2.0f && 
                    ball.x - ball.radius <= -config.active_niveau.Obstacles[i].Panneaux[j].x + config.active_niveau.Obstacles[i].Panneaux[j].largeur / 2.0f && ball.speedX < 0) {
                    ball.speedX = -ball.speedX;
                    ball.x = ball.x+1.0;
                    //std::cout << "touché sens inverse murx : " << -config.active_niveau.Obstacles[i].Panneaux[j].x <<endl;
                    config.active_niveau.Obstacles[i].Panneaux[j].impact = true;
                    // if (-config.active_niveau.Obstacles[i].Panneaux[j].x < ball.x + ball.radius + 1.0)
                    // {
                    //   std::cout << "ouaos2 "<<endl;
                    //     ball.speedY = 0; 
                    //     ball.speedZ = 0; 
                    // }
                }
                
                
            }
        }
    }





        


        
    


        float square_size = 6.0f;
        if (ball.x < (0.0f) || ball.x + ball.radius < (0.0f)){    
            if (ball.y >= (mouseY - square_size/2.0f) and 
            ball.y <= (mouseY + square_size/2.0f) and
            ball.z >= (mouseZ - square_size/2.0f) and 
            ball.z <= (mouseZ + square_size/2.0f)) {

                if (ball.x-ball.radius < (0) && ball.speedX < 0  ){
                    ball.speedX = -ball.speedX;
                }
                
                ball.x = ball.x+1.0;
                ball.speedY = (ball.y - mouseY)*coefRaquette; 
                ball.speedZ = (ball.z - mouseZ)*coefRaquette; 
                
            }
        }
        

        
        ball.y += ball.speedY * deltaTime;
        ball.z += ball.speedZ * deltaTime;
        if (run==false)
        {   
        ball.x += (ball.speedX) * deltaTime;
        }else {
            if (ball.speedX < 0){
                ball.x += (ball.speedX) * deltaTime; 
            }
        }
        
        

    }


    void stickyBall(Ball& ball,float mouseY, float mouseZ) {
        
        ball.x = 0.0f;
        ball.y = mouseY;
        ball.z = mouseZ;

    }

    void check_dead(Ball& ball){
        std::cout << ball.x << std::endl; 
        if (ball.x < (-1.0f)){ //balle derrière la raquette
                config.Dead();
                std::cout << "test" << std::endl;
                game_status = false;
                ball.speedY = 0; 
                ball.speedZ = 0; 
                
        } 
    }   


    Mur tunnel[] = {
        
        {-profondeur/16,0.0,(hauteur/2),largeur,profondeur/8,0.0},
        {-profondeur/16.0f,-(largeur/2.0f),0.0,hauteur,profondeur/8,90.0},
        {-profondeur/16,0.0,-(hauteur/2),largeur,profondeur/8,0.0},
        {-profondeur/16.0f,(largeur/2.0f),0.0,hauteur,profondeur/8,90.0}
        
    };

    void drawMur(Mur mur,GLuint texture) {

        
        
            
        //glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();
            
            glTranslatef(mur.x,mur.y,mur.z);
        
            glRotatef(mur.orientation, 1.0, 0.0, 0.0);
        
            //glScalef(mur.largeur,mur.hauteur,1.0);
            glScalef(mur.profondeur,mur.hauteur,1.0);
            
            drawSquare(true);
            
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

    }

    void drawTunnel(Mur tunnel[],GLuint texture) {

        glPushMatrix();
        for (int j = 0; j < 4; j++){
            for (int i = 0; i < 4; i++)
            {   
    if (j==0){
        if (i%2 ==0){
            glColor3f(0.0, 0.0, 0.8); //(bleu clair)
        }else{
            glColor3f(0.0, 0.0, 0.5); //(bleu assombri)
        }
        if (i==2)
        {
            glColor3f(0.0, 0.0, 0.3);
        }
        
    }
    else if (j==1){
        
            if (i%2 ==0){
            glColor3f(0.0, 0.0, 0.7); // (bleu-gris)
        }else{
            glColor3f(0.0, 0.0, 0.4); //(bleu assombri)
        }
        if (i==2)
        {
            glColor3f(0.0, 0.0, 0.2);
        }
    }
    else if (j==2){
        if (i%2 ==0){
            glColor3f(0.0, 0.0, 0.6); //(bleu moyen)
        }else{
            glColor3f(0.0, 0.0, 0.2); //(bleu assombri)
        }
        if (i==2)
        {
            glColor3f(0.0, 0.0, 0.2);
        }

    }
    else if (j==3){
        
        if (i%2 ==0){
            glColor3f(0.0, 0.0, 0.5); //(bleu foncé) 
        }else{
            glColor3f(0.0, 0.0, 0.1);//(bleu assombri)
        }
        if (i==2)
        {
            glColor3f(0.0, 0.0, 0.1);
        }
    }


                
            
                drawMur(tunnel[i],texture);
                
            }
            glTranslated(-profondeur/8,0.0,0.0);
        }

        glPopMatrix();

        glPushMatrix();
            glColor3f(0.0,0.0,0.0);
            glTranslated(-profondeur/2,0.0,0.0);
            glRotated(90,0.0,1.0,0.0);
            glScalef(20.0f, 30.0f, 1.0);
            drawSquare(true); 
        glPopMatrix();
    }

    Button button1 = {0.0f, 12.0f, 30.0f, 10.0f};
    Button button2 = {0.0f, 0.0f, 30.0f, 10.0f};
    Button button3 = {0.0f, -12.0f, 30.0f, 10.0f};



    void drawButton(Button button) {
        glPushMatrix();
            glTranslatef(0.0f, button.y, button.z);
            glRotatef(90.0, 0.0, 1.0, 0.0); 
            glScalef(10.0f, 30.0f, 1.0f);
            drawSquare(true);
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
        float y = 0.0f;
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
                drawSquare(true);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            // Déplacer le curseur de dessin vers la droite pour le prochain chiffre
            y += 2.5f;
        }
    }

    void drawLives(int lives,GLuint texture) {
        // Calculer la position x, y et z de la première sphère
        float x = 0.0f;
        float y = -15.0f;
        float z = -15.0f;

        // Dessiner chaque sphère correspondant à une vie
        for (int i = 0; i < lives; i++) {
            glPushMatrix();
            glTranslatef(x, y + i * 3.0f, z);
            glRotatef(-90,1.0,0.0,0.0);
            glRotatef(90,0.0,1.0,0.0);
            drawSphere(texture);
            glPopMatrix();
        }
    }




void drawLine(float z){
    glPushMatrix();
        glRotatef(90.0,0.0,1.0,0.0); 
         glBegin(GL_LINE_LOOP);
            glVertex3f(xGraph+(hauteur/2)-0.1, yGraph+(largeur/2)-0.1, z);
            glVertex3f(xGraph-(hauteur/2)+0.1,yGraph+(largeur/2)-0.1, z);
            glVertex3f(xGraph-(hauteur/2)+0.1,yGraph-(largeur/2)+0.1, z);
            glVertex3f(xGraph+(hauteur/2)-0.1,yGraph-(largeur/2)+0.1, z);
        glEnd();
       
    glPopMatrix();
}

//tableau des lignes
// std::vector<Line> lignesInit(float profondeur, float espaceObstacle) {
//     std::vector<Line> lignes;
//     for (float i = -profondeur; i < 0; i += espaceObstacle) {
//         Line ligne = {i};
//         lignes.push_back(ligne);
//     } 
//           std::cout << "----------"<< std::endl; 
//     return lignes;
// }
std::vector<Line> lignes = {{-180}, {-170},{-160}, {-150}, {-140}, {-130}, {-120}, {-110},{-100}, {-90}, {-80}, {-70}, {-60}, {-50}, {-40}, {-30}, {-20}, {-10}};//lignesInit(profondeur, espaceObstacle);


void drawlines(){

    for (int i = 0; i < lignes.size(); i++){
        if(lignes[i].profondeur > 0){
            lignes.erase(lignes.begin() + i);
            Line newLigne = {-profondeur}; 
            lignes.push_back(newLigne); 
        };    
    }
    

    for (int i = 0; i < lignes.size(); i++){
        glPushMatrix();
            float color[3];
            getColor(lignes[i].profondeur, color);
            glColor3f(color[0], color[1], color[2]);
            drawLine(lignes[i].profondeur);   
        glPopMatrix(); 
    } 
}

    void drawObstacle(vector<Obstacle> obstacles){

        for (int i = 0; i < config.active_niveau.Obstacles.size(); i++)
        {
            for (int j = 0; j < config.active_niveau.Obstacles[i].Panneaux.size(); j++)
            {
                if (config.active_niveau.Obstacles[i].Panneaux[j].x < 0)
                {
                    glPushMatrix();
                        
                        if(config.active_niveau.Obstacles[i].Panneaux[j].impact == true){
                            glColor3f( 1.0, 1.0, 1.0);
                            config.active_niveau.Obstacles[i].Panneaux[j].impact = false;
                            
                        }else {


                            float color[3];
                            getColor(config.active_niveau.Obstacles[i].Panneaux[j].x, color);
                            glColor3f(color[0], color[1], color[2]);
                        }
                    
                        glTranslatef(config.active_niveau.Obstacles[i].Panneaux[j].x, config.active_niveau.Obstacles[i].Panneaux[j].y, config.active_niveau.Obstacles[i].Panneaux[j].z);
                        glRotatef(90, 0.0,1.0,0.0);
                        glRotatef(90, 0.0,0.0,1.0);
                        glScalef(config.active_niveau.Obstacles[i].Panneaux[j].hauteur, config.active_niveau.Obstacles[i].Panneaux[j].largeur,1.0);
                        drawSquare(true);  
                    glPopMatrix();
                        
                }
            }
        }
        

        

            
    }



    void drawBonus(vector<Bonus> Bonus){

        for (int i = 0; i < Bonus.size(); i++)
        {
            if (Bonus[i].forme == 0 && Bonus[i].x < 0)
            {
                glPushMatrix();
                    glTranslatef(Bonus[i].x, Bonus[i].y, Bonus[i].z);
                        glColor3f(1.0,1.0,1.0);
                        glRotatef(Bonus[i].angle,1.0,0.5,0.0);
                        glScalef(3.0, 3.0,3.0);
                        drawCube();  
                glPopMatrix();
            
                
            }

            if (Bonus[i].forme == 1 && Bonus[i].x < 0)
            {
                glPushMatrix();
                    glTranslatef(Bonus[i].x, Bonus[i].y, Bonus[i].z);
                        glColor3f(1.0,1.0,1.0);
                        glRotatef(Bonus[i].angle,1.0,0.5,0.0);
                        glScalef(3.0, 3.0,3.0);
                        drawPrism();  
                glPopMatrix();
            
                
            }
            
            
        
        }

    }

    bool isObstacleAtTargetPosition(const Obstacle& obstacle, float targetPosition) {
        for (const Panneau& panneau : obstacle.Panneaux) {
            float obstacleRightPosition = panneau.x;
            if (obstacleRightPosition <= targetPosition) {
                return false;
            }
        }
        return true;
        
    }

    bool areAllObstaclesPastTargetPosition(const vector<Obstacle>& obstacles, float targetPosition) {
        for (const Obstacle& obstacle : obstacles) {
            if (!isObstacleAtTargetPosition(obstacle, targetPosition)) {
                return false;
            }
        }
        return true;
    }




void drawCorridor(float deltaTime){

    if(run==true && game_status == true){
        std::cout << lignes.size()<< std::endl; 
        for (int i = 0; i < lignes.size(); i++)
        {
            lignes[i].profondeur+= vitesse_joueur * deltaTime ; 
            std::cout << lignes[i].profondeur<< std::endl; 
            positionJoueur += 1 * deltaTime;
            config.score = positionJoueur;

            
        }

        for (int i = 0; i < config.active_niveau.Obstacles.size(); i++)
        {
            for (int j = 0; j < config.active_niveau.Obstacles[i].Panneaux.size(); j++)
            {
                config.active_niveau.Obstacles[i].Panneaux[j].x += vitesse_joueur * deltaTime;
                config.active_niveau.Bonus[i].x += vitesse_joueur * deltaTime;
            }
        }



        
        	
	}
        // Vérifie si tous les obstacles ont dépassé la position cible
        float targetPosition = 0.0f;  // La position cible est 0
        if (areAllObstaclesPastTargetPosition(config.active_niveau.Obstacles, targetPosition)) {
            // Tous les obstacles ont dépassé la position cible
            // Effectuez les actions appropriées ici
            config.load_level(config.active_niveau_index+1);
            
            
            
        }

       
            
        
           //drawSection(espaceObstacle, i);
            //std::cout << run << std::endl;
 
    drawlines();
    drawObstacle(config.active_niveau.Obstacles);
    drawBonus(config.active_niveau.Bonus);
    
    
}







    //Si obstacle alors 
        //drawLignes
        //drawObstacle(niveau (1, 2 ou 3),  obstacle (random))
            //Pour tout les pannaux de l'obstacle dessiner pan
    //Sinon
        //drawLigneS










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


