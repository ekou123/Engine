#pragma once
#include "Component.h"
#include "PositionComponent.h"
#include "Actor.h"
#include "Constants.h"
#include "MapComponent.h"
#include "TileMap.h"
#include <iostream>

class GravityComponent : public Component {
public:
    GravityComponent(float strength, float terminalVel = 1000.0f) : g(strength), vmax(terminalVel), vy(0.0f) {}

    void init() override {
		// Initialize the component
		std::cout << "GravityComponent initialized with g: " << g << " and vmax: " << vmax << std::endl;
        vy = 0.0f;
	}
    void update(float dt) override {
        if (!enabled) return;

        auto* pos = owner->getComponent<PositionComponent>();
        // 2) get map
        auto* mapComp = owner->getComponent<MapComponent>();
        if (!pos || !mapComp) return;

        TileMap* map = mapComp->getMap();
        if (!map) {
            std::cerr << "GravityComponent: No map found!" << std::endl;
            return;
        }


        // 3) integrate velocity
        vy = std::min(vy + g * dt, vmax);
        float newY = pos->y + vy * dt;

        // 4) simple ground check: bottom‐left and bottom‐right corners
        bool onGround =
            map->isSolidWorldPos(pos->x, newY + PLAYER_HEIGHT) ||
            map->isSolidWorldPos(pos->x + PLAYER_WIDTH, newY + PLAYER_HEIGHT);

        if (onGround) {
            // snap to top of the tile we hit
            int tileY = int((newY + PLAYER_HEIGHT) / TILE_SIZE);
            pos->y = tileY * TILE_SIZE - PLAYER_HEIGHT;
            vy = 0;
        }
        else {
            pos->y = newY;
        }
    }

    void setOwner(Actor* actor) {
		owner = actor;
	}

    Actor* getOwner() {
        return owner;
    }

    float getGravity() const {
		return g;
	}
private:
    float g = 9.8;
    float vmax;
    float vy;
};