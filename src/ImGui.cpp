#include "../Hammer/include/HammerEngine/HammerEngine.h"
#include "../Hammer/lib/imgui/imgui.h"
#include "../Hammer/lib/imgui/imgui_impl_glfw.h"
#include "../Hammer/lib/imgui/imgui_impl_vulkan.h"

#include "system.h"
#include "ImGui.h"
#include "map.h"

void recordImGuiCommands() {
	ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int winWidth, winHeight; // win does not stand for windows, fuck windows
	glfwGetWindowSize(Engine->window, &winWidth, &winHeight);

    ImGui::SetNextWindowPos(ImVec2(winWidth - 300, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, winHeight), ImGuiCond_FirstUseEver);

	// Combine flags to lock position and disable resizing
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

	bool p_open = true;
	ImGui::Begin("Left Locked Window", &p_open, flags);
    ImGui::Text("heheh do wahtever u want >:}");
    std::string temp1_str = "FPS: " + std::to_string(Engine->FPS);

    const char* c_str = temp1_str.c_str();

    ImGui::Text("%s", c_str);

    if(ImGui::Button("2d view top down edit")) {
    	currentViewMode = 0;
    	cameraChange = 1;
    }

    if(ImGui::Button("3d viewing mode")) {
    	currentViewMode = 1;
    	cameraChange = 1;
    }

    if(currentViewMode == 0){
    	ImGui::Text("chose high of the tile");
    	if (ImGui::Button("Tile high, 0")) {
    		currentTileSpawnHigh = 0;
    	}
    	if (ImGui::Button("Tile high, 1")) {
    		currentTileSpawnHigh = 1;
    	}
    	if (ImGui::Button("Tile high, 2")) {
    		currentTileSpawnHigh = 2;
    	}
    	if (ImGui::Button("Tile high, 3")) {
    		currentTileSpawnHigh = 3;
    	}
    	if (ImGui::Button("Tile high, 4")) {
    		currentTileSpawnHigh = 4;
    	}
    	if (ImGui::Button("Tile high, 5")) {
    		currentTileSpawnHigh = 5;
    	}
    	if (ImGui::Button("Tile high, 6")) {
    		currentTileSpawnHigh = 6;
    	}
    	if (ImGui::Button("Tile high, 7")) {
    		currentTileSpawnHigh = 7;
    	}
		if (ImGui::Button("Tile high, 8")) {
    		currentTileSpawnHigh = 8;
    	}
    	if (ImGui::Button("Tile high, 9")) {
    		currentTileSpawnHigh = 9;
    	}

    	std::string temp2_str = "Current high of spawning tile: " + std::to_string(currentTileSpawnHigh);

	    const char* c2_str = temp2_str.c_str();

	    ImGui::Text("%s", c2_str);
    }

    ImGui::End();
}