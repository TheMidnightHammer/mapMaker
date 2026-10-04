/*
 * Copyright (c) 2026 MidnightHammer-code
 * This source code is licensed under the GPL 3.0 license
 * LICENSE file in the root directory of this source tree.
 */

#include "../Hammer/include/HammerEngine/HammerEngine.h"
#include "../Hammer/lib/imgui/imgui.h"
#include "../Hammer/lib/imgui/imgui_impl_glfw.h"
#include "../Hammer/lib/imgui/imgui_impl_vulkan.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "map.h"
#include "system.h"
#include "ImGui.h"


int main() {
    HammerInfo info(true, 1920, 1080, "Hammer", 1000, false, 0.1f, 1024.0f, 1024*1024*16);

    Engine = new HammerEngine(info);
    Engine->initWindow();
    Engine->initVulkan();
    Engine->InitImgui();

    std::string vPath = "shaders/vert.spv";
    std::string fPath = "shaders/frag.spv";
    
    mainPipeline = new HammerPipeline(
        Engine, vPath, fPath, 1, true, nullptr
    );

    mainTexture = new HammerTexture(
        Engine, "base/base_terrain_texture.jpeg", HammerTextureFilter::Nearest
    );

    std::vector<Vertex> localVertices = {
        {{-0.5f,  0.0f,-0.5f}, {1.0f, 0.0f, 0.0f}, {0.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.0f,-0.5f}, {0.0f, 1.0f, 0.0f}, {1.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.0f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
    };

    std::vector<uint32_t> localIndices = {
        0, 1, 2, 2, 3, 0
    };

    // Allocate the mesh with new and push the pointer
    sceneMesh = new HammerMesh(
        Engine, 
        mainPipeline, 
        mainTexture, 
        localVertices, 
        localIndices
    );
    Engine->meshs.push_back(sceneMesh);

    Engine->cameraPosition = glm::vec3(0, 50, 0);

    Engine->cameraFront = glm::vec3(0,0,0);

    init();

    // --- Main Loop ---
    Engine->drawPassStart();
    while (!glfwWindowShouldClose(Engine->window)) {
        Engine->updateFrameTimeStart();

        if(cameraChange == 1){
	        if (currentViewMode == 1) {
	        	Engine->cameraPosition = glm::vec3(0,50,0);
                Engine->pitch = -89;
                Engine->yaw = 0;
                glm::vec3 front;
                front.x = cos(glm::radians(Engine->yaw)) * cos(glm::radians(Engine->pitch));
                front.y = sin(glm::radians(Engine->pitch));
                front.z = sin(glm::radians(Engine->yaw)) * cos(glm::radians(Engine->pitch));
                Engine->cameraFront = glm::normalize(front);
	        } else if (currentViewMode == 0){
	        	Engine->cameraPosition = glm::vec3(0,50,0);
	        	Engine->pitch = -89;
	        	Engine->yaw = 0;
	        	glm::vec3 front;
			    front.x = cos(glm::radians(Engine->yaw)) * cos(glm::radians(Engine->pitch));
			    front.y = sin(glm::radians(Engine->pitch));
			    front.z = sin(glm::radians(Engine->yaw)) * cos(glm::radians(Engine->pitch));
			    Engine->cameraFront = glm::normalize(front);
	    	}
	    	cameraChange = 0;
    	}

    	if (currentViewMode == 1) {
        	Engine->updateCameraDefault3D();
        } else if (currentViewMode == 0){
        	// Engine->updateCameraDefault2D();
        	if(glfwGetKey(Engine->window, GLFW_KEY_W)){
        		Engine->cameraPosition.x += Engine->cameraSpeed;
        	}
        	if(glfwGetKey(Engine->window, GLFW_KEY_S)){
        		Engine->cameraPosition.x -= Engine->cameraSpeed;
        	}
        	if(glfwGetKey(Engine->window, GLFW_KEY_D)){
        		Engine->cameraPosition.z += Engine->cameraSpeed;
        	}
        	if(glfwGetKey(Engine->window, GLFW_KEY_A)){
        		Engine->cameraPosition.z -= Engine->cameraSpeed;
        	}
    	}

        recordImGuiCommands();

        ImGui::Render();

        updateMouse();
        
        Engine->drawFrame();

        sleepForTargetFPS();

        Engine->updateFrameTimeEnd();
    }
    Engine->drawPassEnd();
    
    // Clean up allocated memory instead of .reset()
    delete mainTexture;
    delete mainPipeline;
    
    Engine->cleanup();

    delete Engine;

    return EXIT_SUCCESS;
}