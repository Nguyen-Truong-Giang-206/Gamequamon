#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <vector>

enum ObstacleType { LOW, HIGH };

struct Obstacle {
    SDL_Rect rect;
    ObstacleType type;
    bool active;

    // Các texture cho vật cản
    SDL_Texture* lowTexture1;  // Texture 1 cho vật cản thấp (chim)
    SDL_Texture* lowTexture2;  // Texture 2 cho vật cản thấp (chim)
    SDL_Texture* highTexture;  // Texture cho vật cản cao

    // Biến dùng cho animation chim
    int frameCount = 0;      // Đếm số frame
    int frameDelay = 10;     // Mỗi 10 frame mới đổi ảnh
    int currentFrame = 0;    // 0 hoặc 1 để chọn ảnh chim

    void loadTextures(SDL_Renderer* renderer);
    void free();
};

void initObstacles(std::vector<Obstacle>& obstacles, SDL_Renderer* renderer);
void updateObstacles(std::vector<Obstacle>& obstacles, int speed);
void renderObstacles(SDL_Renderer* renderer, std::vector<Obstacle>& obstacles);

#endif
