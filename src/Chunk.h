#pragma once
#include <vector>
#include "Constants.h"

struct Chunk {
	int cx, cy;
	std::vector<int> tiles;

	Chunk(int cx, int cy);

	void generate();

	int getTile(int localX, int localY) const;
};