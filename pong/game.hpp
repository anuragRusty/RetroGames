#ifndef PLAYER_H
#define PLAYER_H

#include "player.hpp"
#include <iostream>
#include <raylib-cpp.hpp>

const int maxWidth = 800;
const int maxHeight = 800;
const float tileSize = 36;
const float pSpeed = 200;

enum GameState {
  MENU,
  RUNNING,
  RUNNING2,
  PAUSED,
};

class Game {
public:
  GameState state = GameState::RUNNING;
  Player player1 = Player(Player1, pSpeed, tileSize, maxWidth, maxHeight);
  Player player2 = Player(Player2, pSpeed, tileSize, maxWidth, maxHeight);
  Player computer = Player(Computer, pSpeed, tileSize, maxWidth, maxHeight);
  Ball ball = Ball(tileSize / 2, pSpeed * 2, maxWidth, maxHeight);
  int screenWidth = maxWidth;
  int screenHeight = maxHeight;
  Game();
  void update(float dt);
  void draw();
};

#endif