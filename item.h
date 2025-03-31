#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>

// Cấu trúc vật phẩm
struct Item {
    SDL_Rect rect;       // Kích thước và vị trí
    bool active;         // Có đang hiển thị không
    SDL_Texture* texture = nullptr; // Ảnh vật phẩm
};

// Các hàm xử lý vật phẩm
void loadItemTexture(Item& item, SDL_Renderer* renderer);
void updateItem(Item& item, int speed, SDL_Rect dino, int& score);
void renderItem(SDL_Renderer* renderer, const Item& item);
void freeItem(Item& item); // Giải phóng ảnh

#endif
