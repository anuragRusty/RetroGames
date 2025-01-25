#ifndef GAME_H
#define GAME_H

#include "../include/button.hpp"
#include "background.hpp"
#include "cart.hpp"
#include <functional>
#include <iostream>
#include <raylib-cpp.hpp>
#include <vector>

using namespace std;

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

private:
  int life = 3;
  Button start = Button(screenWidth / 3, screenHeight / 3, screenHeight / 16,"START", BTN_COLOR);
  Button exit = Button(screenWidth / 3, screenHeight / 3 + (screenHeight / 16),screenHeight / 16, "EXIT", BTN_COLOR);
  Button paused = Button(screenWidth - (6 * 1.3 * (screenHeight / 16)),screenHeight - (screenHeight / 16), screenHeight / 16,"PAUSED", BTN_COLOR);
  Button restart = Button(screenWidth - (7 * 1.3 * (screenHeight / 16)),screenHeight - (screenHeight / 16), screenHeight / 16,"RESTART", BTN_COLOR);
  Button resume = Button(screenWidth - (6 * 1.3 * (screenHeight / 16)),screenHeight - (screenHeight / 16), screenHeight / 16,"RESUME", BTN_COLOR);
  GameState state = MENU;
  Background background = Background(screenWidth, screenHeight);
  Cart cart = Cart((screenHeight / 6), screenHeight - (screenHeight / 6),screenHeight / 400, 200);
  Plane plane = Plane(screenHeight / 6, 300);
  vector<Gift> gifts;

  void spawnGift();
  void removeGift();
  void resetGame();
  void updateGifts(float &dt);
  void drawState(string str);
  void drawGifts(Texture2D &texture);

public:
  void update(float dt);
  void draw(Texture2D &texture);
};

#endif