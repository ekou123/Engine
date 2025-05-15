#pragma once
#include "Module.h"
#include <iostream>
#include "Engine.h"
#include "Camera.h"
#include "Player.h"
#include "PlayerModule.h"
#include "PositionComponent.h"
#include "Constants.h"

struct CameraModule : Module {
    Camera cam{ 0,0,WINDOW_W,WINDOW_H };
    PlayerModule* playerModule = nullptr;

    bool init(Engine*) override { 
        Camera& camera = cam;
        // center on player


        PositionComponent* posComp = playerModule->getPlayer()->getComponent<PositionComponent>();
        if (!posComp) {
            std::cerr << "[CameraModule] Cannot find player position component.\n";
            return false;
        }

        float playerX = posComp->x,
            playerY = posComp->y;

        camera.x = playerX + Player::WIDTH / 2.0f - WINDOW_W / 2.0f;
        camera.y = playerY + Player::HEIGHT / 2.0f - WINDOW_H / 2.0f;
        // clamp...
        //camera.x = 0;
        //camera.y = 0;
        
        /*camera.x = std::clamp(camera.x, 0.0f, maxX);
        camera.y = std::clamp(camera.y, 0.0f, maxY);*/
        
        return true;
    }

    void update(Engine&, float) override {
        Camera& camera = cam;
        // center on player
        

        PositionComponent* posComp = playerModule->getPlayer()->getComponent<PositionComponent>();
        if (!posComp) {
			std::cerr << "[CameraModule] Cannot find player position component.\n";
			return;
		}

        //std::cerr << "X: " << posComp->x << "Y: " << posComp->y << std::endl;



        float playerX = posComp->x,
			  playerY = posComp->y;

        camera.x = playerX + Player::WIDTH / 2.0f - WINDOW_W / 2.0f;
        camera.y = playerY + Player::HEIGHT / 2.0f - WINDOW_H / 2.0f;
        // clamp...
    }

    void render(Engine&) override {}
    void shutdown(Engine&) override {}

    void setPlayerModule(PlayerModule* p) { playerModule = p; }

    void setCamera(Camera* c) { cam = *c; }
};