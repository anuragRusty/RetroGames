#include "../libs/button.cpp"
#include "ball.cpp"
#include <functional>
#include <iostream>
#include <raylib.h>
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

  void drawState(string text) {
    float x = screenWidth / 2 - (text.size() / 2.5) * TILE_SIZE;
    float y = screenHeight / 3;
    DrawText(text.c_str(), x, y, TILE_SIZE, WHITE);
  }

public:
  string title = "breakout";
  float screenWidth = 800;
  float screenHeight = 800;
  float scale = 4;

  Button start = Button(screenWidth / 4 + TILE_SIZE, screenHeight / 4,
                        TILE_SIZE, "START", WHITE);
  Button exit = Button(screenHeight / 4 + TILE_SIZE,
                       screenWidth / 4 + TILE_SIZE, TILE_SIZE, "EXIT", WHITE);
  Button paused =
      Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "PAUSE", WHITE);
  Button restart =
      Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "RESTART", WHITE);
  Button resume =
      Button(0, screenHeight - TILE_SIZE, TILE_SIZE, "RESUME", WHITE);

  Grid grid = Grid(screenWidth, 4, scale);
  Player player = Player(screenWidth, screenHeight, scale, 240);
  Ball ball = Ball(screenWidth, screenHeight, scale / 4, 360);

  void update(float dt) {
    function<void()> game_func = [&]() { state = GameState::RUNNING; };
    function<void()> pause_game = [&]() { state = GameState::PAUSED; };
    function<void()> exit_func = [&]() { CloseWindow(); };
    function<void()> restart_game = [&]() {
      Grid grid = Grid(screenWidth, 4, scale);
      Player player = Player(screenWidth, screenHeight, scale, 240);
      Ball ball = Ball(screenWidth, screenHeight, scale / 4, 360);
      game_func();
    };

    switch (state) {
    case GameState::MENU:
      start.onClick(game_func);
      exit.onClick(exit_func);
      break;
    case GameState::RUNNING:
      player.update(dt);
      ball.update(dt, player, grid);
      grid.update();
      paused.onClick(pause_game);
      break;
    case GameState::PAUSED:
      resume.onClick(game_func);
      break;
    case GameState::GAME_OVER:
      restart.onClick(restart_game);
      break;
    }

    if (player.life <= 0) {
      state = GameState::GAME_OVER;
    }
  }

  void draw(Texture2D texture) {
    switch (state) {
    case GameState::MENU:
      start.draw();
      exit.draw();
      break;
    case GameState::RUNNING:
      player.draw(texture);
      ball.draw(texture);
      grid.draw(texture);
      break;
    case GameState::PAUSED:
      drawState("GAME PAUSED");
      resume.draw();
      break;
    case GameState::GAME_OVER:
      drawState("GAME OVER");
      restart.draw();
      break;
    }
  }
};
