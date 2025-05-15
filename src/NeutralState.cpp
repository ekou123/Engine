#include "NeutralState.h"
#include "PositionComponent.h"
#include "MapComponent.h"
#include "TileMap.h"
#include "Player.h"
#include "Constants.h"
#include <iostream>

const float PLAYER_SPEED = 300.0f; // pixels per second

void NeutralState::handleInput(const bool* keystate, float dt) {
	if (keystate[SDL_SCANCODE_SPACE]) {
		std::cout << "Space key pressed in Neutral State\n";
		stateMachine->changeState(activePlayer->jumpingState);
	}

	PositionComponent* pos = getActivePlayer()->getComponent<PositionComponent>();
	if (!pos) {
		std::cout << "PositionComponent not found in NeutralState::handleInput\n";
		return;
	}
	
	MapComponent* mapComp = getActivePlayer()->getComponent<MapComponent>();
	if (!mapComp) {
		std::cout << "MapComponent not found in NeutralState::handleInput\n";
		return;
	}
	TileMap* map = mapComp->getMap();

	float oldX = pos->x;
	float oldY = pos->y;

	// 2) Figure out dx and dy
	float dx = 0;
	if (keystate[SDL_SCANCODE_A]) dx = -PLAYER_SPEED * dt;
	if (keystate[SDL_SCANCODE_D]) dx = +PLAYER_SPEED * dt;
	// dy is already applied by your GravityComponent→ PositionComponent

	// 3) HORIZONTAL PASS
	pos->x += dx;
	{
		// sample just above your feet to avoid “standing” collision:
		float sampleY = pos->y + PLAYER_HEIGHT - 1.0f;
		// left‐side corner
		if (map->isSolidWorldPos(pos->x, sampleY) ||
			map->isSolidWorldPos(pos->x + PLAYER_WIDTH, sampleY))
		{
			pos->x = oldX;  // undo
		}
	}
}

