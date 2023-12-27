#include "player.cpp"
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

  Game() {}

  void update(float dt) {
    switch (state) {
    case MENU:
      break;
    case RUNNING:
      player1.update(dt, screenWidth, screenHeight, ball);
      player2.update(dt, screenWidth, screenHeight, ball);
      ball.update(dt, player1.rec, player2.rec, maxWidth, maxHeight);
      break;
    case RUNNING2:
      player1.update(dt, screenWidth, screenHeight, ball);
      computer.update(dt, screenWidth, screenHeight, ball);
      ball.update(dt, player1.rec, computer.rec, maxWidth, maxHeight);
      break;
    case PAUSED:
      break;
    }
  }

  void draw() {
    switch (state) {
    case MENU:
      break;
    case RUNNING:
      player1.draw();
      player2.draw();
      ball.draw();
      break;
    case RUNNING2:
      player1.draw();
      computer.draw();
      ball.draw();
      break;
    case PAUSED:
      break;
    }
  }
};
