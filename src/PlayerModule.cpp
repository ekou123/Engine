#include "PlayerModule.h"
#include "Engine.h"         // now we have Engine’s full definition
#include <SDL3/SDL.h>
#include <iostream>

// Define each member — note the “PlayerModule::” prefix!

bool PlayerModule::init(Engine* E) {
    // nothing special yet
    return true;
}

void PlayerModule::update(Engine& E, float dt) {
    if (!player || !tileMap) return;
    const bool* ks = SDL_GetKeyboardState(NULL);
    player->update(ks, dt, *tileMap);
}

void PlayerModule::render(Engine& E) {
    if (!camera) {
        std::cerr << "[PlayerModule] Cannot render: missing camera\n";
        return;
    }
    if (!player) {
        std::cerr << "[PlayerModule] Cannot render: missing player\n";
        return;
    }
    player->render(E.renderer, *camera);
}

void PlayerModule::shutdown(Engine& E) {
    // nothing to clean up
}