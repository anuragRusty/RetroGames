#ifndef GAME_H
#define GAME_H

#include "../include/button.hpp"
#include "ball.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
using namespace std;

const float TILE_SIZE = 48;

enum GameState {
  MENU,
  PAUSED,
  RUNNING,
  GAME_OVER,
};

class Game {
private:
  GameState state = MENU;
  void drawState(string text);

public:
  string title = "breakout";
  float screenWidth = 800;
  float screenHeight = 800;
  float scale = 4;
  Button start = Button(screenWidth / 4 + TILE_SIZE, screenHeight / 4,TILE_SIZE, "START", WHITE);
  Button exit = Button(screenHeight / 4 + TILE_SIZE,screenWidth / 4 + TILE_SIZE, TILE_SIZE, "EXIT", WHITE);
  Button paused = Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "PAUSE", WHITE);
  Button restart = Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "RESTART", WHITE);
  Button resume = Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "RESUME", WHITE);
  Grid grid = Grid(screenWidth, 4, scale);
  Player player = Player(screenWidth, screenHeight, scale, 240);
  Ball ball = Ball(screenWidth, screenHeight, scale / 4, 360);

  void update(float dt);
  void draw(Texture2D texture);
};

#endif