#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string> // cần thiết để dùng std::string

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

bool checkCollision(SDL_Rect a, SDL_Rect b);
void renderScore(SDL_Renderer* renderer, TTF_Font* font, int score, SDL_Color color);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color); // ✅ thêm dòng này

#endif
