#include "Menu.h"
#include <string>
#include "Utils.h"


int showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* background) {
    SDL_Event e;
    SDL_Color color = {0, 0, 0};

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Tạo surface và texture cho từng độ khó
    SDL_Surface* surfaceEasy = TTF_RenderText_Solid(font, "De", color);
    SDL_Surface* surfaceMedium = TTF_RenderText_Solid(font, "Trung binh", color);
    SDL_Surface* surfaceHard = TTF_RenderText_Solid(font, "Kho", color);

    SDL_Texture* textureEasy = SDL_CreateTextureFromSurface(renderer, surfaceEasy);
    SDL_Texture* textureMedium = SDL_CreateTextureFromSurface(renderer, surfaceMedium);
    SDL_Texture* textureHard = SDL_CreateTextureFromSurface(renderer, surfaceHard);

    // Tiêu đề menu
    SDL_Surface* surfaceTitle = TTF_RenderText_Solid(font, "Chon do kho:", color);
    SDL_Texture* textureTitle = SDL_CreateTextureFromSurface(renderer, surfaceTitle);

    // Canh giữa màn hình theo chiều ngang
    SDL_Rect titleRect = {
        (WINDOW_WIDTH - surfaceTitle->w) / 2,
        100,
        surfaceTitle->w,
        surfaceTitle->h
    };

    SDL_Rect easyRect = {
        (WINDOW_WIDTH - surfaceEasy->w) / 2,
        200,
        surfaceEasy->w,
        surfaceEasy->h
    };

    SDL_Rect mediumRect = {
        (WINDOW_WIDTH - surfaceMedium->w) / 2,
        270,
        surfaceMedium->w,
        surfaceMedium->h
    };

    SDL_Rect hardRect = {
        (WINDOW_WIDTH - surfaceHard->w) / 2,
        340,
        surfaceHard->w,
        surfaceHard->h
    };

    bool selecting = true;
    int level = -1;

    while (selecting) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return -1;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) return -1;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (x >= easyRect.x && x <= easyRect.x + easyRect.w &&
                    y >= easyRect.y && y <= easyRect.y + easyRect.h) {
                    level = 0;
                    selecting = false;
                } else if (x >= mediumRect.x && x <= mediumRect.x + mediumRect.w &&
                           y >= mediumRect.y && y <= mediumRect.y + mediumRect.h) {
                    level = 1;
                    selecting = false;
                } else if (x >= hardRect.x && x <= hardRect.x + hardRect.w &&
                           y >= hardRect.y && y <= hardRect.y + hardRect.h) {
                    level = 2;
                    selecting = false;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, textureTitle, NULL, &titleRect);
        SDL_RenderCopy(renderer, textureEasy, NULL, &easyRect);
        SDL_RenderCopy(renderer, textureMedium, NULL, &mediumRect);
        SDL_RenderCopy(renderer, textureHard, NULL, &hardRect);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(surfaceEasy);
    SDL_FreeSurface(surfaceMedium);
    SDL_FreeSurface(surfaceHard);
    SDL_FreeSurface(surfaceTitle);

    SDL_DestroyTexture(textureEasy);
    SDL_DestroyTexture(textureMedium);
    SDL_DestroyTexture(textureHard);
    SDL_DestroyTexture(textureTitle);

    return level;
}

bool showGameOver(SDL_Renderer* renderer, TTF_Font* font, int score, SDL_Texture* background) {
    SDL_Event e;
    SDL_Color color = { 255, 0, 0 }; // 🔴 Màu đỏ

    const int centerX = WINDOW_WIDTH / 2;

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return true;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                // Nếu nhấn vào vùng nút Exit
                if (x >= centerX - 50 && x <= centerX + 50 && y >= 250 && y <= 290) {
                    return true; // quay lại menu chọn độ khó
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        // Các dòng chữ được canh giữa màn hình
        renderText(renderer, font, "GAME OVER", centerX - 80, 100, color);
        renderText(renderer, font, "Score: " + std::to_string(score), centerX - 80, 160, color);
        renderText(renderer, font, "Exit", centerX - 30, 250, color);

        SDL_RenderPresent(renderer);
    }

    return false;
}

