#include "simulation.h"


Simulation::Simulation(int width_, int height_) {
	this->width = width_;
	this->height = height_;
}


void Simulation::drawBoids() const{
	for (Boid *boid : this->boids) {
		boid->draw();
	}
}

void Simulation::addBoid() {
	float x = rand() % width;
	float y = rand() % height;

	float vx = rand() % 10;
	float vy = rand() % 10;

	double theta = ((float)rand() / (float)RAND_MAX) * 2 * PI;
	Vector2 randomVelocity = { (float)cos(theta), (float)sin(theta) };

	Boid* newBoid = new Boid(this);
	newBoid->position.x = x;
	newBoid->position.y = y;
	
	newBoid->velocity = randomVelocity;
	
	this->boids.push_back(newBoid);
}

void Simulation::removeBoid() {
	this->boids.pop_back();
}

void Simulation::setNumberBoids() {

	if (this->boids.size() > (int)boidsNumber) {
		while (this->boids.size() > (int)boidsNumber) {
			this->removeBoid();
		}
	}
		
	if (this->boids.size() < (int)boidsNumber) {
		while (this->boids.size() < (int)boidsNumber) {
			addBoid();
		}
	}

}

void Simulation::updateBoids() {
	this->setNumberBoids();
	for (Boid* boid : this->boids) {
		boid->computeForce();
	}
	for (Boid* boid : this->boids) {
		boid->update(&mouseClickPosition);
	}
	this->resetTracking = 0;
}


