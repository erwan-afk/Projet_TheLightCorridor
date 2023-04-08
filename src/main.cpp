#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <iostream>

#include "3D_tools.h"
#include "draw_scene.h"


/* Window properties */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;
static float focal = 60.0; 

double x, y = 0.0; 

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

bool start = false;
double deltaTime = 0.0;




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
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_R :
				flag_animate_rot_arm = 1-flag_animate_rot_arm;
				break;
			case GLFW_KEY_T :
				flag_animate_rot_scale = 1-flag_animate_rot_scale;
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
				game_status = true;
				break;
			default:
				std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
}

void cursor_position_callBack(GLFWwindow* window, double xpos, double ypos){
  
     //getting cursor position
     glfwGetCursorPos(window, &xpos, &ypos);

    x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
    y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

	y = y*std::tan(((focal*M_PI)/180)/2) * dist_zoom;
	x = x*std::tan(((focal*M_PI)/180)/2) * dist_zoom;

    }



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

	glfwSetCursorPosCallback(window, cursor_position_callBack);

    onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	
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

//		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera(); 

		/* Initial scenery setup */
		
		//drawTunnel_base();
		drawTunnel(tunnel);
		drawBall(myball);
		//drawMur(mur);
		drawRaquette(x,y); 
		
		
		//utiliser le temps écoulé pour mettre à jour la position de la balle
		if (game_status)
		{
			updateBall(myball, deltaTime,x, y);
		}
		
		
		

		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS); // Démarre un groupe de points
    	glVertex3f(0.0f, 0.0f, 0.0f); // Ajoute un point au milieu de l'écran
    	glEnd(); // Termine le groupe de points
		


		/* Scene rendering */

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

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