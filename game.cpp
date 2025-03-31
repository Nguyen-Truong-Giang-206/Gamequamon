#include "Game.h"
#include "Dino.h"
#include "Obstacle.h"
#include "Item.h"
#include "Menu.h"
#include "Utils.h"
#include <SDL_image.h>
#include <vector>
#include <string>

void runGame(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* background, int difficulty) {
    bool quit = false, paused = false;
    SDL_Event e;

    // Khởi tạo khủng long
    Dino dino;
    dino.init(renderer); // Truyền renderer vào hàm init

    // Tốc độ game tùy theo độ khó
    int speed = 5 + difficulty * 2;

    // Khởi tạo vật cản
    std::vector<Obstacle> obstacles;
    initObstacles(obstacles, renderer);  // Sửa tại đây

    // Vật phẩm cộng điểm
    Item item = {{800, 200, 30, 30}, false};
    loadItemTexture(item, renderer);

    int score = 0;
    int frameCount = 0;
    int obstaclesPassed = 0;
    int itemCooldown = 0;

    Uint32 frameStart;
    const int frameDelay = 1000 / 60; // 60 FPS

    while (!quit) {
        frameStart = SDL_GetTicks();

        // Xử lý sự kiện
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                paused = !paused;
            }

            if (!paused) {
                dino.handleEvent(e);
            }
        }

        if (paused) continue;

        // Cập nhật khủng long
        dino.update(0.5f, 10.0f);

        // Cập nhật vật cản
        for (auto& ob : obstacles) {
            ob.rect.x -= speed;

            // Nếu vật cản ra khỏi màn hình
            if (ob.rect.x + ob.rect.w < 0) {
                ob.rect.x = 800 + rand() % 300;
                ob.active = true;

                // Random lại loại vật cản
                bool isLow = rand() % 2;
                if (isLow) {
                    ob.rect.h = 40;
                    ob.rect.y = WINDOW_HEIGHT - 80 - ob.rect.h;
                    ob.type = LOW;
                } else {
                    ob.rect.h = 60;
                    ob.rect.y = WINDOW_HEIGHT - ob.rect.h;
                    ob.type = HIGH;
                }

                obstaclesPassed++;

                // Mỗi 5 vật cản sẽ khởi động lại cooldown xuất hiện item
                if (obstaclesPassed >= 5) {
                    obstaclesPassed = 0;
                    itemCooldown = 120; // ~2 giây ở 60 FPS
                }
            }
        }

        // Quản lý thời gian xuất hiện vật phẩm
        if (!item.active && itemCooldown > 0) {
            itemCooldown--;
            if (itemCooldown == 0 && rand() % 100 < 30) { // 30% xuất hiện
                item.active = true;
                item.rect.x = 850;
                item.rect.y = (rand() % 2 == 0) ? 220 : 280;
            }
        }

        // Cập nhật vật phẩm và điểm
        updateItem(item, speed, dino.rect, score);

        // Tăng điểm mỗi 5 frame
        frameCount++;
        if (frameCount % 5 == 0) {
            score++;
        }

        // Kiểm tra va chạm
        for (auto& ob : obstacles) {
            if (ob.active && checkCollision(dino.rect, ob.rect)) {
                showGameOver(renderer, font, score, background);
                return;
            }
        }

        // Vẽ toàn bộ màn hình
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL); // Nền

        dino.render(renderer);
        renderObstacles(renderer, obstacles);
        renderItem(renderer, item);

        // Hiển thị điểm số
        SDL_Color color = {0, 0, 0};
        renderScore(renderer, font, score, color);

        SDL_RenderPresent(renderer);

        // Giới hạn FPS
        int frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
            freeItem(item);
        }
    }
}
