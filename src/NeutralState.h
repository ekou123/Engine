#pragma once
#include "State.h"
#include "Player.h"
#include "StateMachine.h"
#include <SDL3/SDL.h>
#include <iostream>

class NeutralState : public State {
public:
	NeutralState(Player* player, StateMachine* stateMachine)
		: State(player, stateMachine) {
		name = "Deez";
	};


	void enter() override {
		std::cout << "Entering Neutral State\n";
	}

	void handleInput(const bool* keystate, float dt) override;

	void update(float deltaTime) override {
		std::cout << "Updating Neutral State\n";
	}

	void exit() override {
		std::cout << "Exiting Neutral State\n";
	}
};
