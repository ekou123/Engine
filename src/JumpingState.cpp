#include "JumpingState.h"
#include "GravityComponent.h"
#include "NeutralState.h"
#include "NeutralState.h"
#include "Player.h"
#include "PositionComponent.h"
#include "State.h"
#include "StateMachine.h"


// … later in your ctor initializer list …
JumpingState::JumpingState(Player* player, StateMachine* sm)
  : State(player, sm)
  // use sqrtf if you’re calculating with floats:
  , jumpSpeed(std::sqrt(2.0f * 
                         player->getComponent<GravityComponent>()->getGravity() 
                       * desiredJumpHeight))
{}

    void JumpingState::enter() {
        std::cout << "[JumpingState] enter\n";
        // turn off normal gravity
        auto* g = activePlayer->getComponent<GravityComponent>();
        if (g) g->enable();

        vy = jumpSpeed;
    }

    void JumpingState::handleInput(const bool* ks, float) {
        // nothing special mid‐jump
    }

    void JumpingState::update(float dt) {
        if (!isGrounded) {
            return;
        }

        PositionComponent* pos = activePlayer->getComponent<PositionComponent>();
        if (!pos) return;

        // 1) integrate our own jump‐gravity
        vy -= activePlayer->getComponent<GravityComponent>()->getGravity() * dt;
        pos->y -= vy * dt;   // note: subtract to go *up*

        // 2) when we start falling (vy <=0), hand back to normal gravity:
        if (vy <= 0.0f) {
            auto* g = activePlayer->getComponent<GravityComponent>();
            if (g) g->enable();

            // switch into a “FallingState” or back to your default:

            stateMachine->changeState(activePlayer->neutralState);
        }
    }

    void JumpingState::exit() {
        std::cout << "[JumpingState] exit\n";
        isGrounded = true;

    }