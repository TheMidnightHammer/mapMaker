#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Hammer/include/HammerEngine/HammerEngine.h"
#include <GLFW/glfw3.h>

inline HammerEngine* Engine;
inline double mousePosX;
inline double mousePosY;

inline double timeSinceLastClick = 1.5; // needs to be over 1.0 if not good clicks will never happends

inline double timeSinceLastFrame = glfwGetTime();

inline HammerMesh* sceneMesh = nullptr;

inline HammerPipeline* mainPipeline = nullptr;

inline HammerTexture* mainTexture = nullptr;

void updateMouse(); // in map.cpp idk why
void sleepForTargetFPS();



inline std::vector<Vertex> baseTileVertices = {
    {{-0.5f,  0.0f,-0.5f}, {1.0f, 0.0f, 0.0f}, {0.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.0f,-0.5f}, {0.0f, 1.0f, 0.0f}, {1.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
    {{-0.5f,  0.0f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
};

inline std::vector<uint32_t> baseTileIndices = {
    0, 1, 2, 2, 3, 0
};

#endif