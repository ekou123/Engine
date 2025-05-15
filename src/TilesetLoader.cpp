#include "TilesetLoader.h"
#include <iostream>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface) {
        std::cerr << "Failed to load surface: " << SDL_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
    }
    return texture;
}