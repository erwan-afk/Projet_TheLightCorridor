#include <iostream>
#include "3D_tools.h"
#include "draw_scene.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "config.h"


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
			case GLFW_KEY_B :
				config.load_level(1);
				std::cout << "Zoom is " << dist_zoom << std::endl;
				break;
			case GLFW_KEY_ESCAPE :
				config.active_scene_index = 0;
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
				if(config.y < (hauteur/2) && config.x < (largeur/2) && config.y > -(hauteur/2) && config.x > -(largeur/2)){
					game_status = true;
				}
				break;
			case GLFW_KEY_UP :
                run = true;
                break;
			default:
				std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
	if (action == GLFW_RELEASE) {
        switch(key) {
            case GLFW_KEY_UP :
                run = false;
                break;
            default:
                std::cout << "Touche non gérée (" << key << ")" << std::endl;
        }
    }
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
    // Make the window's context current		
	
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
		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_DEPTH_TEST);

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