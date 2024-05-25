#pragma once


#include <raylib.h>
#include <vector>
#include "simulation_specs.h"

class Simulation;

class Boid {
public:
    Boid(Simulation* simulation);
    void update(Vector2 *mouseClickPosition);
    void draw();
    void computeForce();
    bool checkIfTriangleContainsPoint(Vector2 point);
    void clickBoidHanlder(Vector2 *point);

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Simulation* simulation;
    bool isMarked = false;
    Color boidColor = WHITE;
   
    Vector2 tip;
    Vector2 leftTip;
    Vector2 rightTip;

    Vector2 tempSeparation;
    Vector2 tempCohesion;
    Vector2 tempAlignment;

};
