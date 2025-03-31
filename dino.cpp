#include "Dino.h"
#include <SDL_image.h>
#include <iostream>

void Dino::init(SDL_Renderer* renderer) {
    rect = {50, 350, 50, 50};
    y = rect.y;
    velocity = 0;
    isJumping = false;
    isCrouching = false;
    isJumpKeyHeld = false;
    frame = 0;
    frameCount = 0;
    state = RUNNING;

    loadTextures(renderer);
}

void Dino::loadTextures(SDL_Renderer* renderer) {
    SDL_Texture* tex;

    tex = IMG_LoadTexture(renderer, "images/dino_run_1.png");

    runTextures.push_back(tex);

    tex = IMG_LoadTexture(renderer, "images/dino_run_2.png");
    if (!tex) { std::cerr << "Lỗi load dino_run_2.png: " << IMG_GetError() << "\n"; exit(1); }
    runTextures.push_back(tex);

    tex = IMG_LoadTexture(renderer, "images/dino_bow_1.png");
    if (!tex) { std::cerr << "Lỗi load dino_bow_1.png: " << IMG_GetError() << "\n"; exit(1); }
    duckTextures.push_back(tex);

    tex = IMG_LoadTexture(renderer, "images/dino_bow_2.png");
    if (!tex) { std::cerr << "Lỗi load dino_bow_2.png: " << IMG_GetError() << "\n"; exit(1); }
    duckTextures.push_back(tex);

    jumpTexture = IMG_LoadTexture(renderer, "images/dino_jump.png");
    if (!jumpTexture) {
        std::cerr << "Lỗi load dino_jump.png: " << IMG_GetError() << "\n"; exit(1);
    }

    dieTexture = IMG_LoadTexture(renderer, "images/dino_die.png");
    if (!dieTexture) {
        std::cerr << "Lỗi load dino_die.png: " << IMG_GetError() << "\n"; exit(1);
    }
}

void Dino::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
            isJumping = true;
            velocity = -14;
            isJumpKeyHeld = true;
            state = JUMPING;
        } else if (e.key.keysym.sym == SDLK_DOWN) {
            if (!isJumping) {
                isCrouching = true;
                rect.h = 30;
                rect.y = 370;
                state = DUCKING;
            } else {
                velocity += 1.5f;
            }
        }
    } else if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_SPACE) isJumpKeyHeld = false;
        if (e.key.keysym.sym == SDLK_DOWN && isCrouching) {
            isCrouching = false;
            rect.h = 50;
            rect.y = y;
            if (!isJumping) state = RUNNING;
        }
    }
}

void Dino::update(float gravity, float jumpPower) {
    if (isJumping) {
        if (isCrouching) {
            isCrouching = false;
            rect.h = 50;
            rect.y = y;
        }

        if (!isJumpKeyHeld && velocity < 0)
            velocity = 0;

        velocity += gravity;
        y += velocity;

        if (y >= 350) {
            y = 350;
            isJumping = false;
            velocity = 0;
            state = isCrouching ? DUCKING : RUNNING;
        }

        rect.y = (int)y;
    }

    frameCount++;
    if (frameCount >= frameDelay) {
        frameCount = 0;
        frame++;
    }
}

void Dino::render(SDL_Renderer* renderer) {
    SDL_Texture* currentTexture = nullptr;

    switch (state) {
        case RUNNING:
            currentTexture = runTextures[frame % runTextures.size()];
            break;
        case JUMPING:
            currentTexture = jumpTexture;
            break;
        case DUCKING:
            currentTexture = duckTextures[frame % duckTextures.size()];
            break;
        case DEAD:
            currentTexture = dieTexture;
            break;
    }

    if (currentTexture)
        SDL_RenderCopy(renderer, currentTexture, NULL, &rect);
}

void Dino::free() {
    for (auto tex : runTextures) SDL_DestroyTexture(tex);
    for (auto tex : duckTextures) SDL_DestroyTexture(tex);
    SDL_DestroyTexture(jumpTexture);
    SDL_DestroyTexture(dieTexture);
}
