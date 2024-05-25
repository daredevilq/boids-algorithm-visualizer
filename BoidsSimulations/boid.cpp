#include "boid.h"
#include "simulation.h"
#include "raymath.h"
#include <iostream>

// Konstruktor klasy Boid
Boid::Boid(Simulation* simulation_) : simulation(simulation_) {}



void Boid::computeForce() {
    Vector2 sumAlignment = Vector2Zero();
    Vector2 localCenterSum = Vector2Zero();
    Vector2 separationTarget = Vector2Zero();


    int boidsInVisualRange = 0;

    for (Boid* otherBoid : this->simulation->boids) {
        if (otherBoid == this) continue;

        float distance = Vector2Distance(this->position, otherBoid->position);

        if (distance < simulation->visualRangeRadius) {

            //alignment
            sumAlignment = Vector2Add(otherBoid->velocity, sumAlignment);

            //cohesion
            localCenterSum = Vector2Add(otherBoid->position, localCenterSum);

            //separation
            Vector2 diff = Vector2Subtract(this->position, otherBoid->position);
            diff = Vector2Scale(diff, 1.0f / (distance * distance));  // U¿yj dystansu do wa¿enia wektora
            separationTarget = Vector2Add(diff, separationTarget);
           

            boidsInVisualRange++;
        }
    }

    if (boidsInVisualRange != 0) {
        //alignment
        Vector2 averageAlignment = Vector2Scale(sumAlignment, 1.0f / boidsInVisualRange);
        averageAlignment = Vector2ClampValue(averageAlignment, this->simulation->maxSpeed, this->simulation->maxSpeed);
        this->tempAlignment = Vector2Subtract(averageAlignment, this->velocity);
        this->tempAlignment = Vector2Normalize(this->tempAlignment);
        this->tempAlignment = Vector2Scale(this->tempAlignment, this->simulation->maxForce);


        //cohesion
        Vector2 localCenter = Vector2Scale(localCenterSum, 1.0f / boidsInVisualRange);
        Vector2 target = Vector2ClampValue(Vector2Subtract(localCenter, this->position), this->simulation->maxSpeed, this->simulation->maxSpeed);
        this->tempCohesion = Vector2Subtract(localCenter, this->position);
        this->tempCohesion = Vector2Normalize(this->tempCohesion);
        this->tempCohesion = Vector2Scale(this->tempCohesion, this->simulation->maxForce);


        //separation
        Vector2 separationTargetAvg = Vector2Scale(separationTarget, 1.0f / boidsInVisualRange);
        separationTargetAvg = Vector2ClampValue(separationTargetAvg, this->simulation->maxSpeed, this->simulation->maxSpeed);
        this->tempSeparation = Vector2Subtract(separationTargetAvg, this->velocity);
        this->tempSeparation = Vector2Normalize(separationTarget);
        this->tempSeparation = Vector2Scale(this->tempSeparation, this->simulation->maxForce);
    }
    else {
        //alignment
        this->tempAlignment = Vector2Zero();
        
        //cohesion
        this->tempCohesion = Vector2Zero();

        //separation
        this->tempSeparation = Vector2Zero();
    }

    //alignment
    this->tempAlignment.x *= this->simulation->alignCoefficient;
    this->tempAlignment.y *= this->simulation->alignCoefficient;


    //cohesion
    this->tempCohesion.x *= this->simulation->cohesionCoefficient;
    this->tempCohesion.y *= this->simulation->cohesionCoefficient;

    //separation
    this->tempSeparation.x *= this->simulation->separationCoefficient;
    this->tempSeparation.y *= this->simulation->separationCoefficient;


    this->acceleration = Vector2Zero();
    this->acceleration = Vector2Add(this->acceleration, this->tempAlignment);
    this->acceleration = Vector2Add(this->acceleration, this->tempCohesion);
    this->acceleration = Vector2Add(this->acceleration, this->tempSeparation);
    

}


// Funkcja update dla aktualizacji pozycji i prêdkoœci boida
void Boid::update(Vector2 *mouseClickPosition) {
 

    // Ograniczenie przyspieszenia do maxForce
    //this->acceleration = Vector2ClampValue(this->acceleration, -this->simulation->maxForce, this->simulation->maxForce);

    // Aktualizacja prêdkoœci i pozycji
    this->velocity = Vector2Add(this->velocity, this->acceleration);
    this->velocity = Vector2ClampValue(this->velocity, this->simulation->minSpeed, this->simulation->maxSpeed);
    this->position = Vector2Add(this->position, this->velocity);

    this->clickBoidHanlder(mouseClickPosition);
    if (simulation->resetTracking == 1)
    {
        this->isMarked = false;
        this->boidColor = WHITE;
    }

    // Owijanie wokó³ ekranu
    if (this->position.x > simulation->width) this->position.x = 0;
    if (this->position.x < 0) this->position.x = simulation->width;
    if (this->position.y > simulation->height) this->position.y = 0;
    if (this->position.y < 0) this->position.y = simulation->height;
}

// Funkcja draw dla rysowania boida
void Boid::draw() {
    

    Vector2 normalizedVelocityVector{ 10 *Vector2Normalize(velocity).x, 10 * Vector2Normalize(velocity).y };

    Vector2 left{normalizedVelocityVector.y * 1 ,  -1 * normalizedVelocityVector.x};
    Vector2 right{ -1 * normalizedVelocityVector.y, 1* normalizedVelocityVector.x };
   
    
    this->tip = Vector2Add(position, normalizedVelocityVector);
    this->leftTip = Vector2Add(position, left);
    this->rightTip = Vector2Add(position, right);

    DrawTriangle(tip, leftTip, rightTip, this->boidColor);
    
    if (this->isMarked)
    {   
        DrawCircleLines(position.x, position.y, simulation->visualRangeRadius, RED);
        DrawLine(position.x, position.y,  (position.x +  (-FORCE_VISUALIZE_MULTIPLIER* acceleration.x)), (position.y+ (-FORCE_VISUALIZE_MULTIPLIER * acceleration.y)), GREEN);
        
        
    }
        
}


bool Boid::checkIfTriangleContainsPoint(Vector2 point) {
    return CheckCollisionPointTriangle(point, this->tip, this->leftTip, this->rightTip);
}

void Boid::clickBoidHanlder(Vector2 *point) {

    if (checkIfTriangleContainsPoint(*point))
    {
       isMarked = true;
       boidColor = RED;
    }
}