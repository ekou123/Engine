#include "Player.h"
#include "Actor.h"
#include <iostream>
#include "Constants.h"
#include "TileMap.h"
#include "NeutralState.h"
#include "GravityComponent.h"
#include "StateMachine.h"
#include "MapComponent.h"
#include "JumpingState.h"
#include "PositionComponent.h"

const float PLAYER_SPEED = 300.0f; // Speed in pixels per second

Player::Player(float startX, float startY, TileMap* tileMap) : x(startX), y(startY) {
    	// Constructor implementation
	// Initialize player position or other attributes if needed
    startX = startX;
    startY = startY;
    
    currentMap = tileMap;
    
    

    if (!getCurrentMap()) {
		std::cerr << "Player: No map found!" << std::endl;
		return;
	}

    addComponent <PositionComponent>();
    addComponent<GravityComponent>(9.8f);
    addComponent<MapComponent>(getCurrentMap());
    getComponent<GravityComponent>()->setOwner(this);

    stateMachine = new StateMachine();

    neutralState = new NeutralState(this, stateMachine);
    jumpingState = new JumpingState(this, stateMachine);

    stateMachine->changeState(neutralState);
    
}

void Player::update(const bool* ks, float dt, const TileMap& map) {
    auto* pos = getComponent<PositionComponent>();
    if (!pos) return;

    // 1) Gravity (via components)
    Actor::update(dt);

    stateMachine->handleInput(ks, dt);

    

    // 4) VERTICAL PASS
    // (Assuming your GravityComponent already snapped you to the floor 
    //  when you landed, you can skip re‐checking here, or implement ceiling/ground checks as needed.)
}



void Player::render(SDL_Renderer* renderer, const Camera& camera) {
    PositionComponent* posComp = getComponent<PositionComponent>();

    if (&camera == nullptr) {
		std::cerr << "Camera is null in Player::Render" << std::endl;
		return;
	}

    SDL_FRect rect = { posComp->x - camera.x, posComp->y - camera.y, WIDTH, HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, &rect);
}