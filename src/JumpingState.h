#include "State.h"
#include "Player.h"
#include "StateMachine.h"
#include "GravityComponent.h"
#include <cmath>    // <-- this is the key
#include <iostream>


class Player;

class JumpingState : public State {
public:
    JumpingState(Player* player, StateMachine* stateMachine);

    void enter() override;

    void handleInput(const bool* ks, float) override;

    void update(float dt) override;

    void exit() override;

private:
    static constexpr float desiredJumpHeight = 100.0f; // pixels
    float jumpSpeed;   // computed from desiredJumpHeight
    float vy = 0.0f;
    bool isGrounded = true;
};