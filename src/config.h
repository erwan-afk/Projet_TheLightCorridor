#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Needed before including GL/glu.h 
// to avoid a compilation error because of CALLBACK pre-processor definition.
// See https://stackoverflow.com/questions/19198244/how-do-i-get-rid-of-these-compiler-errors-in-glu-h#comment28407913_19198244
// It's usually defined in a system header to define the default calling convention for callbacks, 
// but if it is defined incorrectly this sort of thing happens.
// windef.h usually defines it is __stdcall
#if defined(_WIN64) || defined(_WIN32)
    #include <windef.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

// important to add this line to use M_PI
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include "niveaux.h"




class Scene;
class Config;

class Scene {
public:
    virtual void execution(GLFWwindow* window, Config* config) = 0;
};

class Config {
public:
    /*Parametre de scenes*/
    std::vector<Scene*> scenes;
    int score = 0;
    int vies = 5;
    int active_scene_index = 0;
    int active_niveau_index = 0;
    Niveau active_niveau = Niveaux_tab[this->active_niveau_index];


    /*Variable de jeu*/
    float x_prev,y_prev = 0.0f;
    float x, y = 0.0; 
    bool start = false;

    Config();
    ~Config();

    void executeActiveScene(GLFWwindow* window);
    void Dead();
    void Restart();
    void load_level(int active_niveau_index);

};

class Game : public Scene {
public:
    Game(Config* config);
    void testfunction();
    void execution(GLFWwindow* window, Config* config) override;

private:
    Config* m_config;
};

class Menu : public Scene {
public:
    Menu(Config* config);
    void execution(GLFWwindow* window, Config* config) override;

private:
    Config* m_config;
};

class Menu_GameOver : public Scene {
public:
    Menu_GameOver(Config* config);
    void execution(GLFWwindow* window, Config* config) override;

private:
    Config* m_config;
};

class Menu_GameWin : public Scene {
public:
    Menu_GameWin(Config* config);
    void execution(GLFWwindow* window, Config* config) override;

private:
    Config* m_config;
};




/* Window properties */
extern unsigned int WINDOW_WIDTH;
extern unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];
extern float aspectRatio;
extern float focal; 
extern const double FRAMERATE_IN_SECONDS;
extern double deltaTime;
extern Config config;

void init_texture();


#endif // CONFIG_H
