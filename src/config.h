#pragma once

#include <vector>
#include "niveaux.h"
#include "3D_tools.h"

class Scene;

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
    bool sticky_ball = false;
    bool m_isClickActive = false;
    /*Dimensions des elements*/
    float raquette_radius = 3.0f;

    Config();
    ~Config();

    void executeActiveScene(GLFWwindow* window);
    void Dead();
    void Restart();
    void SetScore(float score);
    void load_level(int active_niveau_index);
    void Bonus_vie();
    void Bonus_sticky();
};

class Scene {
public:
    virtual void execution(GLFWwindow* window, Config* config) = 0;
};

class Game : public Scene {
public:
    Game(Config* config);
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
    bool lock_interaction = true;
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

class Menu_niveau : public Scene {
public:
    Menu_niveau(Config* config);
    void execution(GLFWwindow* window, Config* config) override;

private:
    Config* m_config;
    bool lock_interaction = true;
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
extern float positionJoueur;

void init_texture();