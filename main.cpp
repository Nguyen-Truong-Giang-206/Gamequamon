#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "Menu.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

int main(int argc, char* argv[]) {
    // Khởi tạo SDL, SDL_ttf, SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init lỗi: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init lỗi: " << TTF_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init lỗi: " << IMG_GetError() << std::endl;
        return 1;
    }

    // Tạo cửa sổ và renderer
    SDL_Window* window = SDL_CreateWindow("T-Rex Runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Tạo window lỗi: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Tạo renderer lỗi: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("ArianaVioleta-dz2k.ttf", 24);
    if (!font) {
        std::cerr << "Lỗi load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Load background
    SDL_Surface* bgSurface = IMG_Load("images/background.png");
    if (!bgSurface) {
        std::cerr << "Lỗi load background.png: " << IMG_GetError() << std::endl;
        return 1;
    }

    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    if (!backgroundTexture) {
        std::cerr << "Lỗi tạo texture từ background.png: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Vòng lặp chính
    bool running = true;
    while (running) {
        int difficulty = showMenu(renderer, font, backgroundTexture);
        if (difficulty == -1) break;

        runGame(renderer, font, backgroundTexture, difficulty);
    }

    // Dọn dẹp
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
