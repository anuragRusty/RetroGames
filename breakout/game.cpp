#include "game.hpp"
#include "ball.hpp"
#include <functional>
#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

void Game::drawState(string text) {
  float x = screenWidth / 2 - (text.size() / 2.5) * TILE_SIZE;
  float y = screenHeight / 3;
  DrawText(text.c_str(), x, y, TILE_SIZE, WHITE);
}

void Game::update(float dt) {
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

void Game::draw(Texture2D texture) {
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
