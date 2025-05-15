#pragma once
#include "Player.h"
#include <string>
#include "StateMachine.h"


class StateMachine;

class Player;

class State {
public:
	State(Player*  player, StateMachine* stateMachine) : activePlayer(player), stateMachine(stateMachine) {}
	virtual ~State() = default;

	virtual void enter() {}

	virtual void handleInput(const bool* keystate, float dt) {}

	virtual void update(float deltaTime) {}

	virtual void physicsUpdate(float deltaTime) {}

	virtual void exit() {}

	Player* getActivePlayer() { return activePlayer; }

	std::string name = "";

	

protected:
	Player* activePlayer = nullptr;
	StateMachine* stateMachine;
};