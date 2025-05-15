#pragma once
#include "Module.h"
#include "WorldModule.h"
#include "PlayerModule.h"
#include "CameraModule.h"
#include "Engine.h"
#include "TileMap.h"
#include "Camera.h"
#include "Player.h"
#include "Camera.h"
#include <iostream>
struct RenderModule : Module {
public:
    bool init(Engine*) override;
    void update(Engine&, float) override;
    void render(Engine& E) override;
    void shutdown(Engine&) override;

    void setWorld(TileMap* mapPtr) { worldMap = mapPtr; }
    void setPlayer(Player* p) { player = p; }
    void setCamera(Camera* c) { camera = c; }

private:
    TileMap* worldMap = nullptr;
    Player* player = nullptr;
    Camera* camera = nullptr;
    SDL_Texture* tileset = nullptr;
};