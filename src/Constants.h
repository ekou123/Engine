#pragma once




// Chunk size in pixels
static constexpr int CHUNK_SIZE = 32;
static constexpr int TILE_SIZE = 32;
static constexpr int PIXELS_PER_CHUNK = CHUNK_SIZE * TILE_SIZE;

// World size in pixels

static constexpr int WORLD_TILES_X = 50 * TILE_SIZE;
static constexpr int WORLD_TILES_Y = 38 * TILE_SIZE; 
// How many blocks fit on the screen +1 for partial
static constexpr int MAP_TILES_X = 25; // 25
static constexpr int MAP_TILES_Y = 19; // 19

// Window size (in pixels)
static constexpr int WINDOW_W = MAP_TILES_X * TILE_SIZE; // 800
static constexpr int WINDOW_H = MAP_TILES_Y * TILE_SIZE; // 608

// Player size (in pixels)
static constexpr int PLAYER_WIDTH = 32;
static constexpr int PLAYER_HEIGHT = 32;


static constexpr float GRAVITY = 800.0f;   // px/sec²
static constexpr float TERMINAL_VEL = 1200.0f;   // px/sec

// Block IDs
enum TileType {
	TILE_EMPTY = 0,
	TILE_DIRT = 1,
};