#include <iostream>
#include "TileMap.h"
#include "BlockRegistry.h"
#include "SDL3/SDL.h"
#include "ChunkManager.h"
#include "Constants.h"


TileMap::TileMap() : chunkManager(new ChunkManager())
{
    // allocate exactly MAP_TILES_Y rows of MAP_TILES_X columns
    name = "TileMap";

    chunkManager->updateAroundPlayer(0, 0, 2);

    
    map.resize(MAP_TILES_Y,
        std::vector<int>(MAP_TILES_X, TILE_EMPTY));

    // fill with dirt below row 10
    for (int y = 0; y < MAP_TILES_Y; ++y) {
        for (int x = 0; x < MAP_TILES_X; ++x) {
            if (y > 10) map[y][x] = TILE_DIRT;
        }
    }
}

//void TileMap::render(SDL_Renderer* renderer,
//    SDL_Texture* tileTexture,
//    const Camera& camera)
//{
//    // which tile row/col the camera’s top‐left sits over
//    int startCol = camera.x / TILE_SIZE;
//    int startRow = camera.y / TILE_SIZE;
//
//    // how many tiles fit on the screen +1 for partial
//    int colsOnScreen = WINDOW_W / TILE_SIZE + 1;
//    int rowsOnScreen = WINDOW_H / TILE_SIZE + 1;
//
//    // clamp to map bounds
//    int endCol = std::min(startCol + colsOnScreen, MAP_TILES_X);
//    int endRow = std::min(startRow + rowsOnScreen, MAP_TILES_Y);
//    startCol = std::max(0, startCol);
//    startRow = std::max(0, startRow);
//
//    SDL_FRect destRect{ 0, 0, TILE_SIZE, TILE_SIZE };
//    SDL_FRect srcRect{ 0, 0, TILE_SIZE, TILE_SIZE };
//
//    for (int y = startRow; y < endRow; ++y) {
//        for (int x = startCol; x < endCol; ++x) {
//            int tileID = map[y][x];
//            if (tileID == TILE_EMPTY) continue;
//
//            srcRect.x = tileID * TILE_SIZE;
//            srcRect.y = 0;
//            destRect.x = x * TILE_SIZE - camera.x;
//            destRect.y = y * TILE_SIZE - camera.y;
//
//            SDL_RenderTexture(renderer, tileTexture, &srcRect, &destRect);
//        }
//    }
//}

void TileMap::render(SDL_Renderer* renderer,
    SDL_Texture* tileTexture,
    const Camera& camera)
{
    std::cout << "Chunk Manager: " << chunkManager << " wx: " << camera.x << " wy: " << camera.y << std::endl;
    // 1) compute which tiles the camera actually covers
    int startTileX = camera.x / TILE_SIZE;
    int startTileY = camera.y / TILE_SIZE;
    int endTileX = (camera.x + WINDOW_W) / TILE_SIZE + 1;
    int endTileY = (camera.y + WINDOW_H) / TILE_SIZE + 1;

    // 2) prepare your src/dest rects
    SDL_FRect srcRect{ 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_FRect destRect{ 0, 0, TILE_SIZE, TILE_SIZE };

    // 3) loop *only* over visible tiles, pulling from ChunkManager
    for (int ty = startTileY; ty < endTileY; ++ty) {
        for (int tx = startTileX; tx < endTileX; ++tx) {
            float wx = tx * TILE_SIZE;
            float wy = ty * TILE_SIZE;

            int tileID = chunkManager->getTileAt(wx, wy);
            if (tileID == TILE_EMPTY) continue;

            srcRect.x = tileID * TILE_SIZE;
            srcRect.y = 0;

            destRect.x = wx - camera.x;
            destRect.y = wy - camera.y;

            
            SDL_RenderTexture(renderer, tileTexture, &srcRect, &destRect);
        }
    }
}

void TileMap::update(float playerX, float playerY) {
    chunkManager->updateAroundPlayer(playerX, playerY, 2);
}

bool TileMap::isSolidWorldPos(float worldX, float worldY) const {
    int tileX = int(worldX) / TILE_SIZE;
    int tileY = int(worldY) / TILE_SIZE;

    //std::cout << "TileMap::isSolidWorldPos: tileX: " << tileX << " tileY: " << tileY << std::endl;

    // TRUE guard against *this* map’s dimensions:
    if (tileY < 0 ||
        tileY >= int(map.size()) ||      // no such row
        tileX < 0 ||
        tileX >= int(map[tileY].size()))  // no such column
    {
        return false;
    }

    int id = map[tileY][tileX];
    return BlockRegistry::getInstance().get(id).isSolid;
}
