#include "Chunk.h"

Chunk::Chunk(int cx_, int cy_)
    : cx(cx_), cy(cy_), tiles(CHUNK_SIZE* CHUNK_SIZE, TILE_EMPTY)
{
    generate();
}

void Chunk::generate() {
    // fill tiles[y*CHUNK_SIZE + x] = ...
}

int Chunk::getTile(int localX, int localY) const {
    return tiles[localY * CHUNK_SIZE + localX];
}



