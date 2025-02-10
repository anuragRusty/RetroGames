#ifndef GAME_H
#define GAME_H

#include "../include/button.hpp"
#include "player.hpp"
#include <functional>
#include <raylib-cpp.hpp>
#include <string>
#include <vector>

const Rectangle BGsrc = Rectangle{0, 16, 800, 800};
const Rectangle BGdest = Rectangle{0, 0, BGsrc.width, BGsrc.height};
const int TILE_SIZE = 16;
const Color BTN_COLOR = WHITE;

enum GameState {
  MENU,
  RUNNING,
  PAUSED,
  GAMEOVER,
};

class Game {
public:
  float screenWidth = 800;
  float screenHeight = 800;
  float scale = 5;

  Game();
  void update(float dt);
  void draw(Texture2D &texture);

private:
  std::vector<Enemy> enemies;
  Player player = Player(screenWidth / 2, screenHeight - (screenHeight / 10),scale, screenWidth);
  size_t level = 0;
  GameState state = MENU;
  Button start = Button(screenWidth / 3, screenHeight / 3, screenHeight / 16,"START", BTN_COLOR);
  Button exit = Button(screenWidth / 3, screenHeight / 3 + (screenHeight / 16),screenHeight / 16, "EXIT", BTN_COLOR);
  Button paused = Button(screenWidth - (6 * 0.65 * (screenHeight / 16)), screenHeight - (screenHeight / 16), screenHeight / 16,"PAUSE", BTN_COLOR);
  Button restart = Button(screenWidth - (7 * 1.3 * (screenHeight / 16)),screenHeight - (screenHeight / 16), screenHeight / 16,"RESTART", BTN_COLOR);
  Button resume = Button(screenWidth - (6 * 1.3 * (screenHeight / 16)),screenHeight - (screenHeight / 16), screenHeight / 16,"RESUME", BTN_COLOR);

  void drawState(string str);
  void spawnEnemy();
  void removeEnemy();
  void resetGame();
};

#endif