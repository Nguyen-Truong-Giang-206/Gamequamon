#ifndef DINO_H
#define DINO_H

#include <SDL.h>
#include <vector>

enum DinoState {
    RUNNING,
    JUMPING,
    DUCKING,
    DEAD
};

class Dino {
public:
    SDL_Rect rect;
    float y;
    float velocity;
    bool isJumping;
    bool isCrouching;
    bool isJumpKeyHeld;

    DinoState state;
    int frame, frameCount;
    const int frameDelay = 6;

    std::vector<SDL_Texture*> runTextures;
    std::vector<SDL_Texture*> duckTextures;
    SDL_Texture* jumpTexture;
    SDL_Texture* dieTexture;

    void init(SDL_Renderer* renderer); // ⚠️ Gọi cái này thay vì init()
    void handleEvent(SDL_Event& e);
    void update(float gravity, float jumpPower);
    void render(SDL_Renderer* renderer);
    void free();

private:
    void loadTextures(SDL_Renderer* renderer);
};

#endif
