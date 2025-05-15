#include "Engine.h"
#include <iostream>

bool Engine::init(const char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init: " << SDL_GetError() << "\n";
        return false;
    }
    window = SDL_CreateWindow(title, w, h, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!window || !renderer) return false;
    for (auto& m : modules)
        if (!m->init(this)) return false;
    running = true;
    return true;
};

void Engine::registerModule(std::unique_ptr<Module> m) {
    modules.push_back(std::move(m));
}

void Engine::run() {
    Uint64 last = SDL_GetTicks();
    SDL_Event e;
    while (running) {
        Uint64 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        // early-out: handle quit
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = false;

        for (auto& m : modules) m->update(*this, dt);
        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);
        for (auto& m : modules) m->render(*this);
        SDL_RenderPresent(renderer);
    }
}

void Engine::shutdown() {
    for (auto& m : modules) m->shutdown(*this);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}