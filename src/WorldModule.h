#pragma once
#include "Module.h"
#include <iostream>
#include "TileMap.h"
#include "BlockRegistry.h"
#include "Constants.h"
#include "Engine.h"

struct WorldModule : Module {
    TileMap* tileSet = new TileMap();

    Camera* camera = nullptr;

    void setCamera(Camera* cam) {
		camera = cam;
	}

    bool init(Engine* engine) override {
        // register blocks once
        auto& R = BlockRegistry::getInstance();
        R.registerBlock({ 0,"empty",false,{0,0,TILE_SIZE,TILE_SIZE} });
        R.registerBlock({ 1,"dirt", true,{1 * TILE_SIZE,0,TILE_SIZE,TILE_SIZE} });

        if (!tileSet) {
            tileSet = new TileMap();
        }

        return true;
    }
    void update(Engine&, float) override {}

    void render(Engine& E) override {
        // acquire camera from another module or global; for now assume it's at index 0

        if (!camera) {
            std::cout << "WorldModule cannot render. No Camera found" << std::endl;
            return;
        }

        if (!tileSet) {
			std::cout << "WorldModule cannot render. No TileMap found" << std::endl;
			return;
		}

        
        tileSet->render(E.renderer, /*tileset*/nullptr, *camera);
    }
    void shutdown(Engine&) override {}
};