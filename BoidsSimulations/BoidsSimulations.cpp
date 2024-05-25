// BoidsSimulations.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#define RAYGUI_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <raylib.h>
#include <raygui.h>
#include "simulation_specs.h"
#include "simulation.h"
#include "boid.h"




int main()
{
    float visualRangeRadiusSlider = 100.0f;


    float separationCoefficientSlider = 0.5;
    float alignCoefficientSlider = 0.3;
    float cohesionCoefficientSlider = 0.5;

    float minSpeedSlider = 1.0f;
    float maxSpeedSlider = 2.0f;
    float maxForceSlider = 0.1f;

    
    //SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(SCREEN_WIDTH, SCREEEN_HEIGHT, "Boid Simulation");
    SetTargetFPS(120);

    Simulation simulation(SCREEN_WIDTH, SCREEEN_HEIGHT);
    simulation.initialBoidNumber = 500;
    simulation.setNumberBoids();
    bool showMessageBox = false;
    long frame = 0;

    while (WindowShouldClose() == false) {

        simulation.visualRangeRadius = visualRangeRadiusSlider;
        simulation.alignCoefficient = alignCoefficientSlider;
        simulation.separationCoefficient = separationCoefficientSlider;
        simulation.cohesionCoefficient = cohesionCoefficientSlider;
        simulation.maxForce = maxForceSlider;
        simulation.maxSpeed = maxForceSlider;

        if (frame % 100 == 1)
        {
            std::cout << "Visual Range" << std::endl;
            std::cout << simulation.visualRangeRadius << std::endl;
            std::cout << "---------------------" << std::endl;
            std::cout << "Align" << std::endl;
            std::cout << simulation.alignCoefficient << std::endl;
            std::cout << "---------------------" << std::endl;
            std::cout << "Separation" << std::endl;
            std::cout << simulation.separationCoefficient << std::endl;
            std::cout << "---------------------" << std::endl;
            std::cout << "Cogesion" << std::endl;
            std::cout << simulation.cohesionCoefficient << std::endl;
            std::cout << "---------------------" << std::endl;
        }
        frame++;


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            simulation.mouseClickPosition = GetMousePosition();
        }
        else {
            simulation.mouseClickPosition.x = -1;
            simulation.mouseClickPosition.y = -1;
        }

        

        // Update simulation
        simulation.updateBoids();
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        simulation.drawBoids();

        GuiSliderBar({ SCREEN_WIDTH - 300, 90, 150, 20 }, "Visual Range", NULL, & visualRangeRadiusSlider, 0, 1000);

        GuiSliderBar({ SCREEN_WIDTH - 300, 120, 150, 20 }, "Align Coefficient", NULL, &alignCoefficientSlider, 0, 1);

        GuiSliderBar({ SCREEN_WIDTH - 300, 150, 150, 20 }, "Separation Coefficient", NULL, &separationCoefficientSlider, 0, 1);

        GuiSliderBar({ SCREEN_WIDTH - 300, 180, 150, 20 }, "Cohesion Coefficient", NULL, &cohesionCoefficientSlider, 0, 1);

        GuiSliderBar({ SCREEN_WIDTH - 300, 210, 150, 20 }, "Maximum Force", NULL, &maxForceSlider, 0, 1);

        GuiSliderBar({ SCREEN_WIDTH - 300, 240, 150, 20 }, "Maximum Speed", NULL, &maxSpeedSlider, 0, 5);

        simulation.resetTracking = GuiButton({ SCREEN_WIDTH - 300, 270, 150, 20 }, "Reset Tracking");

        EndDrawing();
    }

    CloseWindow();
}

