#include "config.h"
#include "niveaux.h"
#include "3D_tools.h"
#include "draw_scene.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <fstream>
#include <sstream>

int x_image;
int y_image;
int n_image;

GLuint jouer;
GLuint rejouer;
GLuint niveaux;
GLuint quiter;
GLuint win;
GLuint textures_nombre[10];
GLuint texture_ball;
GLuint texture_mur;

GLuint load_texture(const std::string& file_path) {
    stbi_set_flip_vertically_on_load(true); // inverse verticalement l'image chargée
    unsigned char* tab = stbi_load(file_path.c_str(), &x_image, &y_image, &n_image, 0);

    GLuint texture_id;
    glGenTextures(1, &texture_id); // génère un identifiant de texture unique
    glBindTexture(GL_TEXTURE_2D, texture_id); // associe l'identifiant de texture à la texture active
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x_image, y_image, 0, GL_RGB, GL_UNSIGNED_BYTE, tab);
    stbi_image_free(tab);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture_id;
}

void init_texture(){
    jouer = load_texture("../textures/jouer.jpg");
	rejouer = load_texture("../textures/rejouer.jpg");
    niveaux = load_texture("../textures/niveaux.jpg");
    quiter = load_texture("../textures/quiter.jpg");

	win = load_texture("../textures/win.jpg");

	texture_ball = load_texture("../textures/metal.jpg");
	texture_mur = load_texture("../textures/mur.jpg");

	for(int i = 0; i < 10; i++) {
		std::string chemin = "../textures/numbers/" + std::to_string(i) + ".jpg";
		textures_nombre[i] = load_texture(chemin);
	}

	
}


/* Window properties */
unsigned int WINDOW_WIDTH = 1000;
unsigned int WINDOW_HEIGHT = 1000;
const char WINDOW_TITLE[] = "The Light Corridor";
float aspectRatio = 1.0;
float focal = 60.0; 
const double FRAMERATE_IN_SECONDS = 1. / 30.;
double deltaTime = 0.0;

Config::Config() {
    // initialisation des scènes
	
    scenes.push_back(new Menu(this));
    scenes.push_back(new Game(this));
	scenes.push_back(new Menu_GameOver(this));
	scenes.push_back(new Menu_GameWin(this));
    // ajouter d'autres scènes ici
}

Config::~Config() {
    // libération de la mémoire allouée pour les scènes
    for (auto scene : scenes) {
        delete scene;
    }
}
void Config::load_level(int index) {
	if (index < Niveaux_tab.size())
	{
		this->active_niveau_index = index;
		this->active_niveau = Niveaux_tab[this->active_niveau_index];

		if (index > 0)
		{
			for (int i = 0; i < config.active_niveau.Obstacles.size(); i++)
		{
			for (int j = 0; j < config.active_niveau.Obstacles[i].Panneaux.size(); j++)
			{
				config.active_niveau.Obstacles[i].Panneaux[j].x -= 90.0;
				config.active_niveau.Bonus[i].x -= 90.0;
			}
		}
		}
		

		
	}else
	{
		this->active_scene_index = 3;
        this->Restart();
		game_status = false;
	}
	
	
    

}

void Config::executeActiveScene(GLFWwindow* window) {
    if (active_scene_index >= 0 && active_scene_index < scenes.size()) {
        scenes[active_scene_index]->execution(window, this);
		
    }
}


void Config::Restart(){
	//probleme pas de reset de score
    config.score = 0;
    config.vies = 5;
	
	load_level(0);
    
}

void Config::Dead(){
    std::cout << this->vies << std::endl;
    if (this->vies > 0)
    {
        this->vies--;
        
    }else
    {
        this->active_scene_index = 2;
        this->Restart();
    } 
}





Game::Game(Config* config) : m_config(config) {}


void Game::execution(GLFWwindow* window, Config* config) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		m_config->x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
		m_config->y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

		
		m_config->y = m_config->y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
		m_config->x = m_config->x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

		if(m_config->y > (hauteur/2) - raquette_radius || m_config->y < -(hauteur/2)+raquette_radius ){
			m_config->y = m_config->y_prev;
		}else {
			m_config->y_prev = m_config->y;
		}

		if(m_config->x > (largeur/2) - raquette_radius || m_config->x < -(largeur/2)+raquette_radius){
			m_config->x = m_config->x_prev;
		}else {
			m_config->x_prev = m_config->x;
		}

		/* Cleaning buffers and setting Matrix Mode */
		

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Initial scenery setup */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		setCamera(); 

		//drawTunnel_base();
		drawTunnel(tunnel,texture_mur);

		
		drawCorridor(deltaTime); 
		

		// Dessiner la balle après avoir dessiné les obstacles
		drawBall(myball, texture_ball);

		drawRaquette(m_config->x, m_config->y);

	
		

		drawScore(m_config->score, textures_nombre);

		drawLives(m_config->vies,texture_ball);
		
		
		if (game_status == true)
		{	
			//on update deux fois pour plus de precision
			
			updateBall(myball, deltaTime/2,m_config->x, m_config->y);
			updateBall(myball, deltaTime/2,m_config->x, m_config->y);
            check_dead(myball); 
            
		}else
		{
			stickyBall(myball,m_config->x, m_config->y);
		}
		
		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS); // Démarre un groupe de points
    	glVertex3f(0.0f, 0.0f, 0.0f); // Ajoute un point au milieu de l'écran
    	glEnd(); // Termine le groupe de points 

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

Menu::Menu(Config* config) : m_config(config) {}

void Menu::execution(GLFWwindow* window, Config* config) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		double xpos, ypos;
		int left_button_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (left_button_state == GLFW_PRESS) {
			glfwGetCursorPos(window, &xpos, &ypos);
			// Traiter le clic ici en utilisant les coordonnées xpos et ypos

			m_config->x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
			m_config->y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

			m_config->y = m_config->y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
			m_config->x = m_config->x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

			if (m_config->x >= -button1.width/2 && m_config->x <= button1.width/2 && m_config->y >= button1.z - button1.height/2 && m_config->y <= button1.z + button1.height/2) {
				// Clic sur le premier bouton
				// Traiter le clic ici
				std::cout << "Jouer" << std::endl;
				m_config->active_scene_index = 1;
				
			} else if (m_config->x >= -button2.width/2 && m_config->x <= button2.width/2 && m_config->y >= button2.z - button2.height/2 && m_config->y <= button2.z + button2.height/2) {
				// Clic sur le deuxième bouton
				// Traiter le clic ici
				std::cout << "Niveau" << std::endl;
			} else if (m_config->x >= -button3.width/2 && m_config->x <= button3.width/2 && m_config->y >= button3.z - button3.height/2 && m_config->y <= button3.z + button3.height/2) {
				// Clic sur le troisième bouton
				// Traiter le clic ici
				std::cout << "Quitter" << std::endl;
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		
		

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Initial scenery setup */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		
		drawMenu(jouer,niveaux,quiter);

		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS); // Démarre un groupe de points
    	glVertex3f(0.0f, 0.0f, 0.0f); // Ajoute un point au milieu de l'écran
    	glEnd(); // Termine le groupe de points 

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}


Menu_GameOver::Menu_GameOver(Config* config) : m_config(config) {}

void Menu_GameOver::execution(GLFWwindow* window, Config* config) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		double xpos, ypos;
		int left_button_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (left_button_state == GLFW_PRESS) {
			glfwGetCursorPos(window, &xpos, &ypos);
			// Traiter le clic ici en utilisant les coordonnées xpos et ypos

			m_config->x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
			m_config->y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

			m_config->y = m_config->y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
			m_config->x = m_config->x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

			if (m_config->x >= -button2.width/2 && m_config->x <= button2.width/2 && m_config->y >= button2.z - button2.height/2 && m_config->y <= button2.z + button2.height/2) {
				// Clic sur le deuxième bouton
				// Traiter le clic ici
				std::cout << "ReJouer" << std::endl;
				m_config->active_scene_index = 1;
			} else if (m_config->x >= -button3.width/2 && m_config->x <= button3.width/2 && m_config->y >= button3.z - button3.height/2 && m_config->y <= button3.z + button3.height/2) {
				// Clic sur le troisième bouton
				// Traiter le clic ici
				std::cout << "Quitter" << std::endl;
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		
		

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Initial scenery setup */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		
		drawMenu(rejouer,rejouer,quiter);

		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS); // Démarre un groupe de points
    	glVertex3f(0.0f, 0.0f, 0.0f); // Ajoute un point au milieu de l'écran
    	glEnd(); // Termine le groupe de points 

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

Menu_GameWin::Menu_GameWin(Config* config) : m_config(config) {}

void Menu_GameWin::execution(GLFWwindow* window, Config* config) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		double xpos, ypos;
		int left_button_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (left_button_state == GLFW_PRESS) {
			glfwGetCursorPos(window, &xpos, &ypos);
			// Traiter le clic ici en utilisant les coordonnées xpos et ypos

			m_config->x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
			m_config->y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

			m_config->y = m_config->y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
			m_config->x = m_config->x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

			if (m_config->x >= -button2.width/2 && m_config->x <= button2.width/2 && m_config->y >= button2.z - button2.height/2 && m_config->y <= button2.z + button2.height/2) {
				// Clic sur le deuxième bouton
				// Traiter le clic ici
				std::cout << "ReJouer" << std::endl;
				m_config->active_scene_index = 1;
				
			} else if (m_config->x >= -button3.width/2 && m_config->x <= button3.width/2 && m_config->y >= button3.z - button3.height/2 && m_config->y <= button3.z + button3.height/2) {
				// Clic sur le troisième bouton
				// Traiter le clic ici
				std::cout << "Quitter" << std::endl;
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		
		

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Initial scenery setup */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		
		drawMenu(win,win,quiter);

		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS); // Démarre un groupe de points
    	glVertex3f(0.0f, 0.0f, 0.0f); // Ajoute un point au milieu de l'écran
    	glEnd(); // Termine le groupe de points 

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}



Config config;