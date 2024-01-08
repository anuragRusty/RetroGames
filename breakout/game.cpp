#include "ball.cpp"
#include <iostream>
#include <raylib.h>
using namespace std;

enum GameState {
  MENU,
  PAUSED,
  RUNNING,
  GAME_OVER,
};

class Game {
private:
  GameState state = MENU;

public:
  string title = "breakout";
  float screenWidth = 800;
  float screenHeight = 800;
  float scale = 4;
  Grid grid = Grid(screenWidth, 4, scale);
  Player player = Player(screenWidth, screenHeight, scale, 240);
  Ball ball = Ball(screenWidth, screenHeight, scale / 4, 360);

  void update(float dt) {
    player.update(dt);
    ball.update(dt, player, grid);
    grid.update();
  }

  void draw(Texture2D texture) {
    player.draw(texture);
    ball.draw(texture);
    grid.draw(texture);
  }
};
