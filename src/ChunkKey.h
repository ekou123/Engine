#pragma once
#include <cstdint>
#include <unordered_map>
#include <functional>
#include "ChunkKey.h"
#include "Chunk.h"
#include "Constants.h"
#include "TileMap.h"


struct ChunkKey {
	int cx, cy;
	bool operator==(ChunkKey const& o) const { return cx == o.cx && cy == o.cy; }

	ChunkKey(int cx, int cy) : cx(cx), cy(cy) {}	
};

struct ChunkKeyHasher {
	size_t operator()(ChunkKey const& k) const noexcept {
		// pack the two 32-bit ints into one 64-bit value
		uint64_t packed =
			(uint64_t(uint32_t(k.cx)) << 32)
			| uint64_t(uint32_t(k.cy));

		// hash that 64-bit integer
		return std::hash<uint64_t>()(packed);
	}
};

using ChunkMap = std::unordered_map<ChunkKey, Chunk, ChunkKeyHasher>;