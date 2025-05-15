#pragma once
// BlockType.h
#pragma once
#include <SDL3/SDL.h>
#include <string>

struct BlockType {
	int      id = 0;
		std::string name = "";
	bool     isSolid = false;
	SDL_Rect srcRect = {};
};