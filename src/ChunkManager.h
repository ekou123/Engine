#pragma once

#include "ChunkKey.h"
#include "ChunkKeyHasher.h"
#include "Constants.h"
#include "TileMap.h"
#include <unordered_map>




class ChunkManager {
    std::unordered_map<ChunkKey, Chunk, ChunkKeyHasher> chunks;

public:
    // get or create a chunk at (cx,cy)
    Chunk& getChunk(int cx, int cy);

    // fetch tile at world‐pixel pos
    int getTileAt(float worldX, float worldY);

    // ensure all chunks in a radius around player are loaded
    void updateAroundPlayer(float playerWorldX, float playerWorldY, int radiusChunks = 2);

};

using ChunkMap = std::unordered_map<ChunkKey, Chunk, ChunkKeyHasher>;