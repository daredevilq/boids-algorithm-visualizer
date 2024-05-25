#pragma once
#include "boid.h"
#include <vector>
class Simulation
	{
	public:
		int initialBoidNumber;
		int height;
		int width;
		float visualRangeRadius = 100; // 100
		float minSpeed = 1.; // 1.
		float maxSpeed = 2.; //2.
		float maxForce = 0.1 ;

		float separationCoefficient = 0.5;
		float alignCoefficient = 0.3;
		float cohesionCoefficient = 0.5;



		Simulation(int width, int height);
		//~Simulation();
		std::vector<Boid*> boids;
		void drawBoids() const;
		void updateBoids();
		void setNumberBoids();
		void addBoid();

	};

