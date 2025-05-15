#include "RenderModule.h"
#include "TilesetLoader.h"
#include "Engine.h"

bool RenderModule::init(Engine* E) {
    tileset = loadTexture(E->renderer, "tileset2.bmp");
    if (!tileset) {
        std::cerr << "[RenderModule] Failed to load tileset\n";
        return false;
    }
    return true;
}

void RenderModule::update(Engine&, float) {
    float playerX = player->getComponent<PositionComponent>()->x;
    float playerY = player->getComponent<PositionComponent>()->y;
    if (!playerX || !playerY) {
		std::cerr << "[RenderModule] Player position component not found.\n";
		return;
	}

    worldMap->update(playerX, playerY);
}

void RenderModule::render(Engine& E) {
    if (!camera || !worldMap || !player) {
        std::cerr << "[RenderModule] Cannot render. Missing camera, world map, or player.\n";
        return;
    }

    if (!tileset) {
		std::cerr << "[RenderModule] Cannot render. Missing tileset.\n";
		return;
	}

    worldMap->render(E.renderer, tileset, *camera);
    player->render(E.renderer, *camera);
}

void RenderModule::shutdown(Engine&) {
    if (tileset) {
        SDL_DestroyTexture(tileset);
        tileset = nullptr;
    }
}