#include "StateMachine.h"
#include "State.h"    // now we see the full definition
#include "Player.h"

StateMachine::~StateMachine() = default;

void StateMachine::changeState(State* newState) {
	if (currentState) {
		currentState->exit();
	}

	currentState = newState;

	if (currentState) {
		currentState->enter();
	}
}

void StateMachine::initialize(State* initialState) {
	currentState = initialState;
	if (currentState) {
		currentState->enter();
	}
}

void StateMachine::setPlayer(Player* player) {
	this->player = player;
}

void StateMachine::handleInput(const bool* keystate, float dt) {
	if (currentState) {
		currentState->handleInput(keystate, dt);
	}
}