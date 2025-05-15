#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "Module.h"
#include "PlayerModule.h"

class Engine {
public:
	Engine() : window(nullptr), renderer(nullptr), running(false) {}
	bool init(const char* title, int w, int h);
	void registerModule(std::unique_ptr<Module> module);
	void registerPlayer(Player* player) { currentPlayer = player; }
	void run();
	void shutdown();

	SDL_Window* window;
	SDL_Renderer* renderer;

private:
	std::vector<std::unique_ptr<Module>> modules;
	Player* currentPlayer = nullptr;
	bool running;
	float deltaTime;
	SDL_Event event;

	//void handleEvents();
	//void updateModules();
	//void renderModules();
	//void shutdownModules();
};