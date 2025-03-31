#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>

int showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* background);
bool showGameOver(SDL_Renderer* renderer, TTF_Font* font, int score, SDL_Texture* background);

#endif
