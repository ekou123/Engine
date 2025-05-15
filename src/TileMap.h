#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include "Camera.h"

//const int TILE_SIZE = 32;
//const int MAP_WIDTH = 800;
//const int MAP_HEIGHT = 608;

class ChunkManager;

class TileMap {
public:
	TileMap();

	std::string name;

	void render(SDL_Renderer* renderer, SDL_Texture* tileSet, const Camera& camera);

	void update(float playerX, float playerY);

	bool isSolidWorldPos(float worldX, float worldY) const;

private:
	std::vector<std::vector<int>> map;
	ChunkManager* chunkManager;
};

