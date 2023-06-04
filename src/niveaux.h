#pragma once
#include "draw_scene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct Panneau{
    float x;          
    float y;
    float z;

    
    float hauteur; 
    float largeur; 

    bool impact;
    
}Panneau;

typedef struct Bonus{
    float x;          
    float y;
    float z;

    int forme;
    int SpeedRotation;
    int angle;
    float taille;
    
}Bonus;

typedef struct Obstacle{
    vector<Panneau> Panneaux;
}Obstacle;


typedef struct Niveau{
    vector<Obstacle> Obstacles;
    vector<Bonus> bonus_items;
}Niveau; 


const Niveau niveau1 = {
    {   //obstacles
        {   //panneaux
            {
                {-40.0, 7.5, 0.0, 15.0, 20.0,false}   
            }
        },
        {
            {
                {-90.0, -7.5, 0.0, 15.0 , 20.0,false}   
            },
        },
        {
            {
                {-140.0, 0.0, 5.0, 30.0, 10.0,false}
     
            }
        },
        {
            {
                {-180.0, 0.0, -5.0, 30.0, 10.0,false} 
            }
        }, 
        {
            {
                {-200.0, 12.5, 0.0, 5.0, 20.0,false},
                {-200.0, -12.5, 0.0, 5.0, 20.0, false}   
            }
        }
        
    },
    {   //bonus
        {
            {-20.0, 7.5, 0.0, 0, 1, 60,3},
            {-20.0, -7.5, 0.0, 1, 1, 60,3} 
        }
    }
};

const Niveau niveau2 = {

    {
        {
            {
                {-30.0, -10.0, 0.0, 10.0, 20.0,false}   
            }
        },
        //--
        {
            {
                {-90.0, 12.5, 0.0, 5.0 , 20.0,false}   
            }
        },
        {
            {
                {-95.0, 10.0, 0.0, 10.0 , 20.0,false}   
            }
        },
        {
            {
                {-100.0, 7.5, 0.0, 15.0, 20.0,false}   
            }
        },
        {
            {
                {-105.0, 5.0, 0.0, 20.0, 20.0,false}   
            }
        },
        //--
        {
            {
                {-155.0, -12.5, 0.0, 5.0 , 20.0,false}   
            }
        },
        {
            {
                {-160.0, -10.0, 0.0, 10.0 , 20.0,false}   
            }
        },
        {
            {
                {-165.0, -7.5, 0.0, 15.0, 20.0,false}   
            }
        },
        {
            {
                {-170.0, -5.0, 0.0, 20.0, 20.0,false}   
            }
        },
        //--
        {
            {
                {-200.0, 0.0, 7.5, 30.0, 5.0,false},
                {-200.0, 0.0, -7.5, 30.0, 5.0, false}   
            }
        }
        
    },
    {
        {
            {-20.0, 7.5, 0.0, 0, 1, 60,3},
            {-20.0, -7.5, 0.0, 1, 1, 60,3} 
        }
    }
};

const Niveau niveau3 = {

    {
        {
         {
                {-20.0, 0.0, 7.5, 30.0, 5.0,false},
                {-20.0, 0.0, -7.5, 30.0, 5.0, false}   
            }
        },
        {
            {
                {-30.0, 0.0, -20.0/3, 30.0,  20.0/3,false},
                {-30.0, 0.0, 20.0/3, 30.0,  20.0/3, false}   
            }
        },
        {
            {
                {-50.0, 12.5, 0.0, 5.0 , 20.0,false},   
                {-50.0, -12.5, 0.0, 5.0 , 20.0,false}   
            }
        },
        {
            {
                {-55.0, 10.0, 0.0, 10.0 , 20.0,false},
                {-55.0, -10.0, 0.0, 10.0 , 20.0,false}
            }
        },
        {  
            {
                {-75.0, 7.5, 0.0, 15.0, 20.0,false}   
            }
        },
        {
         {
                {-100.0, 0.0, 0.0, 5.0, 20.0,false},
                {-100.0, 0.0, 0.0, 30.0, 5.0, false}   
            }
        }
        
    },
    {
        {
            {-20.0, 7.5, 0.0, 0, 1, 60,3},
            {-20.0, -7.5, 0.0, 1, 1, 60,3} 
        }
    }
};

const std::vector<Niveau> Niveaux_tab = {niveau1, niveau2, niveau3};

