#pragma once


#include <raylib.h>
#include <vector>

class Simulation;

class Boid {
public:
    Boid(Simulation* simulation);
    void update();
    void draw() const;
    void alignment();
    void cohesion();
    void separation();
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Simulation* simulation;


    Vector2 tempSeparation;
    Vector2 tempCohesion;
    Vector2 tempAlignment;

};
