#ifndef MAP_H
#define MAP_H


#include <cstdint>
#include <vector>
#include "../Hammer/include/HammerEngine/HammerEngine.h"

inline uint8_t currentTileSpawnHigh = 1;

inline std::vector<std::vector<uint8_t>> map;


void placeTile(uint8_t tileHigh, float locationX, float locationY);
void init();
void updateMesh();

#endif