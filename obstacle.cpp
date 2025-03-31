#include "Obstacle.h"
#include <cstdlib>
#include <ctime>
#include "Utils.h"
#include <SDL_image.h>
#include <iostream>

const int OBSTACLE_LOW_GAP = 80; // khoảng trống giữa vật cản thấp và mặt đất

void Obstacle::loadTextures(SDL_Renderer* renderer) {
    // Tải ảnh vật cản thấp - Ảnh 1
    lowTexture1 = IMG_LoadTexture(renderer, "images/bird_1.png");
    if (!lowTexture1) {
        std::cerr << "Lỗi load low_obstacle_1.png: " << IMG_GetError() << "\n";
        exit(1);
    }

    // Tải ảnh vật cản thấp - Ảnh 2
    lowTexture2 = IMG_LoadTexture(renderer, "images/bird_2.png");
    if (!lowTexture2) {
        std::cerr << "Lỗi load low_obstacle_2.png: " << IMG_GetError() << "\n";
        exit(1);
    }

    // Tải ảnh vật cản cao
    highTexture = IMG_LoadTexture(renderer, "images/obstacle.png");
    if (!highTexture) {
        std::cerr << "Lỗi load high_obstacle.png: " << IMG_GetError() << "\n";
        exit(1);
    }
}

void Obstacle::free() {
    // Giải phóng bộ nhớ texture của vật cản
    if (lowTexture1) {
        SDL_DestroyTexture(lowTexture1);
    }
    if (lowTexture2) {
        SDL_DestroyTexture(lowTexture2);
    }
    if (highTexture) {
        SDL_DestroyTexture(highTexture);
    }
}

void initObstacles(std::vector<Obstacle>& obstacles, SDL_Renderer* renderer) {
    srand(time(NULL));
    obstacles.clear();
    for (int i = 0; i < 2; ++i) {
        Obstacle ob;
        ob.rect.w = 30;

        bool isLow = rand() % 2;

        if (isLow) {
            ob.rect.h = 40; // chiều cao vật cản thấp
            ob.rect.y = WINDOW_HEIGHT - OBSTACLE_LOW_GAP - ob.rect.h; // tạo khoảng trống
            ob.type = LOW;
        } else {
            ob.rect.h = 60; // chiều cao vật cản cao
            ob.rect.y = WINDOW_HEIGHT - ob.rect.h; // sát mặt đất
            ob.type = HIGH;
        }

        ob.rect.x = 800 + i * 400;
        ob.active = true;

        // Tải texture cho vật cản
        ob.loadTextures(renderer);

        obstacles.push_back(ob);
    }
}

void updateObstacles(std::vector<Obstacle>& obstacles, int speed) {
    for (auto& ob : obstacles) {
        ob.rect.x -= speed;
        if (ob.rect.x + ob.rect.w < 0) {
            ob.rect.x = 800 + rand() % 200;

            bool isLow = rand() % 2;

            if (isLow) {
                ob.rect.h = 40;
                ob.rect.y = WINDOW_HEIGHT - OBSTACLE_LOW_GAP - ob.rect.h;
                ob.type = LOW;
            } else {
                ob.rect.h = 60;
                ob.rect.y = WINDOW_HEIGHT - ob.rect.h;
                ob.type = HIGH;
            }
        }
    }
}

void renderObstacles(SDL_Renderer* renderer, std::vector<Obstacle>& obstacles) {
    for (auto& ob : obstacles) {
        SDL_Texture* currentTexture = nullptr;

        // Nếu là chim thì cập nhật animation đập cánh chậm lại
        if (ob.type == LOW) {
            ob.frameCount++;
            if (ob.frameCount >= ob.frameDelay) {
                ob.frameCount = 0;
                ob.currentFrame = (ob.currentFrame + 1) % 2; // Chuyển frame 0 -> 1 -> 0 ...
            }
            currentTexture = (ob.currentFrame == 0) ? ob.lowTexture1 : ob.lowTexture2;
        } else {
            currentTexture = ob.highTexture;
        }

        // Vẽ vật cản
        if (currentTexture) {
            SDL_RenderCopy(renderer, currentTexture, NULL, &ob.rect);
        }
    }
}

