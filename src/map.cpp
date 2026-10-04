#include "map.h"
#include "ImGui.h"
#include "system.h"
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>
#include <cmath>

void init() {
	int rows = 2048;
	int cols = 2048;

	map.resize(rows, std::vector<uint8_t>(cols, 0));

	map[0][0] = 1; // for the first one which is not create in here but create in the main function
}


void updateMouse() {
    glfwGetCursorPos(Engine->window, &mousePosX, &mousePosY);
    int windowWidth, windowHeight;
    glfwGetWindowSize(Engine->window, &windowWidth, &windowHeight);

    if (currentViewMode == 0) {
        if (glfwGetMouseButton(Engine->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double currentTime = glfwGetTime();
            if(currentTime - timeSinceLastClick > 0.15f) {
                timeSinceLastClick = currentTime;

                float windowCenterX = windowWidth / 2.0f;
                float windowCenterY = windowHeight / 2.0f;

                float cameraHeight = Engine->cameraPosition.y; // 50.0f
                
                float fovDegrees = 45.0f; 
                float fovRadians = fovDegrees * (3.14159265f / 180.0f);

                float visibleWorldHeight = 2.0f * cameraHeight * std::tan(fovRadians / 2.0f);
                float pixelsPerTile = windowHeight / visibleWorldHeight;

                float pixelOffsetX = mousePosX - windowCenterX;
                float pixelOffsetY = mousePosY - windowCenterY;

                float tileOffsetX = -pixelOffsetY / pixelsPerTile;
                float tileOffsetZ = pixelOffsetX / pixelsPerTile;

                float pitchOffset = cameraHeight * std::tan(1.0f * (3.14159265f / 180.0f));

                float tileX = Engine->cameraPosition.x + pitchOffset + tileOffsetX;
                float tileY = Engine->cameraPosition.z + tileOffsetZ;

                placeTile(currentTileSpawnHigh, tileX, tileY);
                updateMesh();
            }
        }
    }
}

void placeTile(uint8_t tileHigh, float locationX, float locationY) {
    assert(tileHigh <= 10);

    int row = static_cast<int>(std::round(locationX));
    int col = static_cast<int>(std::round(locationY));

    if (row >= 0 && row < 2048 && col >= 0 && col < 2048) {
        map[row][col] = tileHigh;
    } else {
        std::cout << "Click ignored: Out of map bounds! (" << row << ", " << col << ")\n";
    }
}



std::vector<Vertex> createMeshFromGrid(const std::vector<std::vector<uint8_t>>& grid) {
    std::vector<Vertex> vertices;

    const std::vector<Vertex> localVertices = {
        {{-0.5f, 0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0000f, 1.0000f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, 0.0f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0000f, 0.0000f}, {1.0f, 0.0f, 0.0f}},
    };

    size_t rows = grid.size();
    size_t cols = rows > 0 ? grid[0].size() : 0;

    std::cout << "rows, cols : " << rows << " " << cols << "\n";

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] == 0) continue; // Skip empty tiles

            std::cout << "generating at: " << row << " " << col << "\n";

            for (const auto& vertex : localVertices) {
                vertices.push_back({
                    {vertex.pos.x + static_cast<float>(row), vertex.pos.y, vertex.pos.z + static_cast<float>(col)},
                    vertex.color,
                    vertex.texCoord,
                    vertex.normal
                });
            }
        }
    }

    return vertices;
}

std::vector<uint32_t> createIndicesForMesh(const std::vector<std::vector<uint8_t>>& grid) {
    std::vector<uint32_t> indices;
    const std::vector<uint32_t> baseTileIndices = { 0, 1, 2, 2, 3, 0 };

    size_t rows = grid.size();
    size_t cols = rows > 0 ? grid[0].size() : 0;

    uint32_t vertexOffset = 0;

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            if (grid[row][col] == 0) continue;

            for (uint32_t index : baseTileIndices) {
                indices.push_back(vertexOffset + index);
            }
            vertexOffset += 4; // Increment by vertex count per tile quad
        }
    }

    return indices;
}

void updateMesh() {
    std::vector<Vertex> vertices = createMeshFromGrid(map);
    std::vector<uint32_t> indices = createIndicesForMesh(map);

    sceneMesh->updateBuffers(vertices, indices);
}