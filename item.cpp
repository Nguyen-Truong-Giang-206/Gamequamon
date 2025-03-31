#include "Item.h"
#include "Utils.h"
#include <SDL_image.h>
#include <iostream>

// Tải ảnh vật phẩm từ file
void loadItemTexture(Item& item, SDL_Renderer* renderer) {
    item.texture = IMG_LoadTexture(renderer, "images/item.png");
    if (!item.texture) {
        std::cerr << "Lỗi tải ảnh item.png: " << IMG_GetError() << "\n";
        exit(1);
    }
}

// Cập nhật vật phẩm: di chuyển, va chạm
void updateItem(Item& item, int speed, SDL_Rect dino, int& score) {
    if (!item.active) return;

    item.rect.x -= speed;

    if (item.rect.x + item.rect.w < 0) {
        item.rect.x = 800 + rand() % 300;  // Đặt lại vị trí random bên phải
        item.active = true;
    }

    if (checkCollision(dino, item.rect)) {
        score += 100;
        item.active = false;
    }
}

// Vẽ vật phẩm bằng ảnh
void renderItem(SDL_Renderer* renderer, const Item& item) {
    if (!item.active || !item.texture) return;
    SDL_RenderCopy(renderer, item.texture, NULL, &item.rect);
}

// Giải phóng ảnh
void freeItem(Item& item) {
    if (item.texture) {
        SDL_DestroyTexture(item.texture);
        item.texture = nullptr;
    }
}
