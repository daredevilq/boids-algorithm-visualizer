#include "boid.h"
#include "simulation.h"
#include "raymath.h"
#include <iostream>

// Konstruktor klasy Boid
Boid::Boid(Simulation* simulation_) : simulation(simulation_) {}

// Funkcja alignment dla wyrównania kierunku poruszania siê boidów
void Boid::alignment() {
    Vector2 sumAlignment = Vector2Zero();
    int boidsInVisualRange = 0;

    for (Boid* otherBoid : this->simulation->boids) {
        if (otherBoid == this) continue;

        float distance = Vector2Distance(this->position, otherBoid->position);

        if (distance < simulation->visualRangeRadius) {
            sumAlignment = Vector2Add(otherBoid->velocity, sumAlignment);
            boidsInVisualRange++;
        }
    }

    if (boidsInVisualRange != 0) {
        Vector2 averageAlignment = Vector2Scale(sumAlignment, 1.0f / boidsInVisualRange);
        averageAlignment = Vector2ClampValue(averageAlignment, this->simulation->maxSpeed, this->simulation->maxSpeed);
        this->tempAlignment = Vector2Subtract(averageAlignment, this->velocity);

        this->tempAlignment = Vector2Normalize(this->tempAlignment);
        this->tempAlignment = Vector2Scale(this->tempAlignment, this->simulation->maxForce);
    }
    else {
        this->tempAlignment = Vector2Zero();
    }

    this->tempAlignment.x *= this->simulation->alignCoefficient;
    this->tempAlignment.y *= this->simulation->alignCoefficient;
}

// Funkcja cohesion dla zachowania spójnoœci stada
void Boid::cohesion() {
    Vector2 localCenterSum = Vector2Zero();
    int boidsInVisualRange = 0;

    for (Boid* otherBoid : this->simulation->boids) {
        if (otherBoid == this) continue;

        float distance = Vector2Distance(this->position, otherBoid->position);

        if (distance < simulation->visualRangeRadius) {
            localCenterSum = Vector2Add(otherBoid->position, localCenterSum);
            boidsInVisualRange++;
        }
    }

    if (boidsInVisualRange != 0) {
        Vector2 localCenter = Vector2Scale(localCenterSum, 1.0f / boidsInVisualRange);


        Vector2 target  = Vector2ClampValue(Vector2Subtract(localCenter, this->position), this->simulation->maxSpeed, this->simulation->maxSpeed);
        this->tempCohesion = Vector2Subtract(localCenter, this->position);

        this->tempCohesion = Vector2Normalize(this->tempCohesion);
        this->tempCohesion = Vector2Scale(this->tempCohesion, this->simulation->maxForce);
    }
    else {
        this->tempCohesion = Vector2Zero();
    }

    this->tempCohesion.x *= this->simulation->cohesionCoefficient;
    this->tempCohesion.y *= this->simulation->cohesionCoefficient;
}

// Funkcja separation dla zachowania oddzielenia boidów
void Boid::separation() {
    Vector2 separationTarget = Vector2Zero();
    int boidsInVisualRange = 0;

    for (Boid* otherBoid : this->simulation->boids) {
        if (otherBoid == this) continue;

        float distance = Vector2Distance(this->position, otherBoid->position);

        if (distance < simulation->visualRangeRadius) {
            Vector2 diff = Vector2Subtract(this->position, otherBoid->position);
            diff = Vector2Scale(diff, 1.0f / (distance * distance));  // U¿yj dystansu do wa¿enia wektora
            separationTarget = Vector2Add(diff, separationTarget);
            boidsInVisualRange++;
        }
    }

    if (boidsInVisualRange != 0) {
        Vector2 separationTargetAvg = Vector2Scale(separationTarget, 1.0f / boidsInVisualRange);
        separationTargetAvg = Vector2ClampValue(separationTargetAvg, this->simulation->maxSpeed, this->simulation->maxSpeed);

        this->tempSeparation = Vector2Subtract(separationTargetAvg, this->velocity);
        this->tempSeparation = Vector2Normalize(separationTarget);
        this->tempSeparation = Vector2Scale(this->tempSeparation, this->simulation->maxForce);
    }
    else {
        this->tempSeparation = Vector2Zero();
    }

    this->tempSeparation.x *= this->simulation->separationCoefficient;
    this->tempSeparation.y *= this->simulation->separationCoefficient;
}

// Funkcja update dla aktualizacji pozycji i prêdkoœci boida
void Boid::update() {
    this->alignment();
    this->cohesion();
    this->separation();

    this->acceleration = Vector2Zero();
    this->acceleration = Vector2Add(this->acceleration, this->tempAlignment);
    this->acceleration = Vector2Add(this->acceleration, this->tempCohesion);
    this->acceleration = Vector2Add(this->acceleration, this->tempSeparation);

    // Ograniczenie przyspieszenia do maxForce
    //this->acceleration = Vector2ClampValue(this->acceleration, -this->simulation->maxForce, this->simulation->maxForce);

    // Aktualizacja prêdkoœci i pozycji
    this->velocity = Vector2Add(this->velocity, this->acceleration);
    this->velocity = Vector2ClampValue(this->velocity, this->simulation->minSpeed, this->simulation->maxSpeed);
    this->position = Vector2Add(this->position, this->velocity);

    // Owijanie wokó³ ekranu
    if (this->position.x > simulation->width) this->position.x = 0;
    if (this->position.x < 0) this->position.x = simulation->width;
    if (this->position.y > simulation->height) this->position.y = 0;
    if (this->position.y < 0) this->position.y = simulation->height;
}

// Funkcja draw dla rysowania boida
void Boid::draw() const {
    DrawCircle(position.x, position.y, 5, RED);
}
