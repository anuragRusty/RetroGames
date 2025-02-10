#ifndef GAME_H
#define GAME_H

#include "../include/button.hpp"
#include "snake.hpp"
#include <functional>
#include <raylib-cpp.hpp>

const float TILE_SIZE = 48;
const float SCREEN_WIDTH = TILE_SIZE * 16;
const float SCREEN_HEIGHT = TILE_SIZE * 16;

enum GameState {
  MENU,
  PAUSED,
  GAMEOVER,
  RUNNING,
};

class Game {
public:
  Snake snake = Snake(TILE_SIZE, TILE_SIZE, TILE_SIZE);
  Food food = Food(TILE_SIZE);
  GameState state = GameState::MENU;
  Button start = Button(SCREEN_WIDTH / 4 + TILE_SIZE, SCREEN_HEIGHT / 4,TILE_SIZE, "START",WHITE);
  Button exit = Button(SCREEN_WIDTH / 4 + TILE_SIZE,SCREEN_HEIGHT / 4 + TILE_SIZE, TILE_SIZE, "EXIT",WHITE);
  Button paused = Button(0, SCREEN_HEIGHT - TILE_SIZE, TILE_SIZE, "PAUSE",WHITE);
  Button restart = Button(0, SCREEN_HEIGHT - TILE_SIZE, TILE_SIZE, "RESTART",WHITE);
  Button resume = Button(0, SCREEN_HEIGHT - TILE_SIZE, TILE_SIZE, "RESUME",WHITE);

  void update(float dt);
  void score();
  void drawState(string text);
  void draw();
};

#endif