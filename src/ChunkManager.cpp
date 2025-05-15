#include "Chunk.h"
#include "ChunkManager.h"
#include "ChunkKey.h"
#include "ChunkKeyHasher.h"
#include "Constants.h"
#include "TileMap.h"
#include <unordered_map>





Chunk& ChunkManager::getChunk(int cx, int cy) {
    ChunkKey key{ cx,cy };
    auto it = chunks.find(key);                  // only one argument!
    if (it == chunks.end())
        it = chunks.emplace(key, Chunk(cx, cy)).first;
    return it->second;
}

    // fetch tile at world‐pixel pos
int ChunkManager::getTileAt(float worldX, float worldY) {
        int tileX = int(worldX) / TILE_SIZE;
        int tileY = int(worldY) / TILE_SIZE;
        int cx = (tileX >= 0 ? tileX : tileX - CHUNK_SIZE + 1) / CHUNK_SIZE;
        int cy = (tileY >= 0 ? tileY : tileY - CHUNK_SIZE + 1) / CHUNK_SIZE;

        Chunk& ch = getChunk(cx, cy);
        int localX = tileX - cx * CHUNK_SIZE;
        int localY = tileY - cy * CHUNK_SIZE;
        return ch.getTile(localX, localY);
    }

    // ensure all chunks in a radius around player are loaded
void ChunkManager::updateAroundPlayer(float playerWorldX, float playerWorldY, int radiusChunks) {
    int pcx = int(playerWorldX) / PIXELS_PER_CHUNK;
    int pcy = int(playerWorldY) / PIXELS_PER_CHUNK;

    for (int dy = -radiusChunks; dy <= radiusChunks; ++dy) {
        for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
            getChunk(pcx + dx, pcy + dy);
        }
    }

        // (Optional) unload distant chunks here to free memory
}

using ChunkMap = std::unordered_map<ChunkKey, Chunk, ChunkKeyHasher>;