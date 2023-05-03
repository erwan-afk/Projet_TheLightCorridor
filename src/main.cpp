#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


#include <iostream>

#include "3D_tools.h"
#include "draw_scene.h"

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int x_image;
int y_image;
int n_image;

GLuint jouer;
GLuint niveaux;
GLuint quiter;
GLuint textures_nombre[10];
GLuint texture_ball;


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
    niveaux = load_texture("../textures/niveaux.jpg");
    quiter = load_texture("../textures/quiter.jpg");

	texture_ball = load_texture("../textures/metal.jpg");

	for(int i = 0; i < 10; i++) {
		std::string chemin = "../textures/numbers/" + std::to_string(i) + ".jpg";
		textures_nombre[i] = load_texture(chemin);
	}

	
}



/* Window properties */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;
static float focal = 60.0; 

float x_prev,y_prev = 0.0f;
float x, y = 0.0; 

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

bool start = false;
double deltaTime = 0.0;

int active_scene_index;




class Config;

class Scene {
public:
	virtual void execution(GLFWwindow* window, Config* config) = 0;
};

class Game : public Scene {
public:

	Game(Config* config) : m_config(config) {}
	
    void execution(GLFWwindow* window, Config* config) override {
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
		y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

		y = y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
		x = x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

		if(y > (hauteur/2) || y < -(hauteur/2) ){
			y = y_prev;
		}else {
			y_prev = y;
		}

		if(x > (largeur/2) || x < -(largeur/2) ){
			x = x_prev;
		}else {
			x_prev = x;
		}

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Initial scenery setup */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		setCamera(); 

		//drawTunnel_base();
		drawTunnel(tunnel);
		

		drawBall(myball,texture_ball);
		//drawMur(mur);
		drawRaquette(x,y); 

		drawScore(150344, textures_nombre);

		drawLives(3,texture_ball);
		
		
		if (game_status == true)
		{
			updateBall(myball, deltaTime,x, y);
		}else
		{
			stickyBall(myball,x, y);
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

	private:
  	Config* m_config;
};



class Menu : public Scene {	
public:

	Menu(Config* config) : m_config(config) {}

	void execution(GLFWwindow* window, Config* config) override {	

		double xpos, ypos;
		int left_button_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (left_button_state == GLFW_PRESS) {
			glfwGetCursorPos(window, &xpos, &ypos);
			// Traiter le clic ici en utilisant les coordonnées xpos et ypos

			x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
			y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

			y = y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
			x = x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

			if (x >= -button1.width/2 && x <= button1.width/2 && y >= button1.z - button1.height/2 && y <= button1.z + button1.height/2) {
				// Clic sur le premier bouton
				// Traiter le clic ici
				std::cout << "Jouer" << std::endl;
				active_scene_index = 1;
				
			} else if (x >= -button2.width/2 && x <= button2.width/2 && y >= button2.z - button2.height/2 && y <= button2.z + button2.height/2) {
				// Clic sur le deuxième bouton
				// Traiter le clic ici
				std::cout << "Niveau" << std::endl;
			} else if (x >= -button3.width/2 && x <= button3.width/2 && y >= button3.z - button3.height/2 && y <= button3.z + button3.height/2) {
				// Clic sur le troisième bouton
				// Traiter le clic ici
				std::cout << "Quitter" << std::endl;
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

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
	
	private:
  	Config* m_config;
};


class Config {
public:
  std::vector<Scene*> scenes;
  
  // autres propriétés de configuration

  Config() {
    // initialisation des scènes
    scenes.push_back(new Menu(this));
    scenes.push_back(new Game(this));
    // ajouter d'autres scènes ici

	active_scene_index = 0;
  }

  ~Config() {
    // libération de la mémoire allouée pour les scènes
    for (auto scene : scenes) {
      delete scene;
    }
  }

  void executeActiveScene(GLFWwindow* window) {
    if (active_scene_index >= 0 && active_scene_index < scenes.size()) {
      scenes[active_scene_index]->execution(window, this);
    }
  }

};



/* Error handling function */
void onError(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(focal,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);

	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;

}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				active_scene_index = 0;
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_KP_9 :
				if(dist_zoom<100.0f) dist_zoom*=1.1;
				std::cout << "Zoom is " << dist_zoom << std::endl;
				break;
			case GLFW_KEY_KP_3 :
				if(dist_zoom>1.0f) dist_zoom*=0.9;
				std::cout << "Zoom is " << dist_zoom << std::endl;
			     double xpos, ypos;	theta += 5;
				break;
			case GLFW_KEY_SPACE :
				if(y < (hauteur/2) && x < (largeur/2) && y > -(hauteur/2) && x > -(largeur/2)){
					game_status = true;
				}
				break;
			default:
				std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
}




Config config;

int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current		glEnable(GL_DEPTH_TEST);
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
    onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	init_texture();

	/* Get time (in second) at loop beginning */
	double startTime = glfwGetTime();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//au début de la boucle, calculer le temps écoulé depuis la dernière image :
		double currentTime = glfwGetTime();
		deltaTime = currentTime - startTime;
		startTime = currentTime;

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* RENDER HERE */


		//activateScene(window);
		config.executeActiveScene(window);


		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

    glfwTerminate();
    return 0;
}