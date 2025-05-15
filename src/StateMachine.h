#pragma once
#include <memory>
#include "State.h"
#include "Player.h"
#include <iostream>

class Player; // Forward declaration
class State; // Forward declaration


class StateMachine {
public:
	~StateMachine();  // out-of-line destructor
	void changeState(State* newState);

	// Add new 

	void initialize(State* initialState);

	void setPlayer(Player* player);

	void handleInput(const bool* keystate, float dt);
private:
	State* currentState = nullptr;
	Player* player = nullptr;
};