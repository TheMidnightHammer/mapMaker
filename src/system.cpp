// nothing ig
#include "system.h"
#include <GLFW/glfw3.h>
#include <iostream>


void sleepForTargetFPS(){
	// 1.0f because glfwGetTime retures in sec not ticks
	int targetFPS = 60;
	double targetMs = 1.0 / targetFPS; // ~0.01666s for 60 FPS
    
    while (glfwGetTime() - timeSinceLastFrame < targetMs - 0.001) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    timeSinceLastFrame = glfwGetTime();
}