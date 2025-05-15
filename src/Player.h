#pragma once
#include <SDL3/SDL.h>
#include "Camera.h"
#include "TileMap.h"
#include "StateMachine.h"
#include "Actor.h"

class State;
class StateMachine;

class Player : public Actor {
public:
	Player(float startX, float startY, TileMap* currentTileMap);
	void update(const bool* keystate, float deltaTime, const TileMap& map);
	void render(SDL_Renderer* renderer, const Camera& camera);
	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float newX) { x = newX; }
	void setY(float newY) { y = newY; }
	void setCamera(Camera* cam) { camera = cam; }
	void setCurrentMap(TileMap* map) { currentMap = map; }
	TileMap* getCurrentMap() { return currentMap; }
	static constexpr int WIDTH = 32;
	static constexpr int HEIGHT = 32;

	State* neutralState = nullptr;
	State* jumpingState = nullptr;
private:
	float x, y;
	StateMachine* stateMachine = nullptr;
	State* currentState = nullptr;
	Camera* camera = nullptr;
	TileMap* currentMap = nullptr;
	
	

};