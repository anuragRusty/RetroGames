#include "game.hpp"
#include "shape.hpp"
#include <raylib.h>
#include <string>

void Game::update(float dt) {
  std::function<void()> handle_start = [&]() { state = GameState::RUNNING; };
  std::function<void()> handle_paused = [&]() { state = GameState::PAUSED; };
  std::function<void()> handle_exit = []() { CloseWindow(); };
  std::function<void()> handle_restart = [&]() {
    resetGame();
    handle_start();
  };
  switch (state) {
  case MENU:
    start.onClick(handle_start);
    exit.onClick(handle_exit);
    break;
  case RUNNING:
    handleState(grid);
    handleShape();
    currShape.update(dt, grid);
    grid.update(score);
    paused.onClick(handle_paused);
    break;
  case PAUSED:
    resume.onClick(handle_start);
    break;
  case GAMEOVER:
    restart.onClick(handle_restart);
    break;
  }
}

void Game::resetGame() {
  grid = Grid();
  currShape = Shape();
  nextShape = Shape();
  score = 0;
}

void Game::handleState(Grid const &grid) {
  if (currShape.exhausted) {
    for (size_t i = 0; i < currShape.sprite.size(); i++) {
      for (size_t j = 0; j < currShape.sprite[i].size(); j++) {
        if (currShape.sprite[i][j]) {
          int x = floor((currShape.vec.x + (i * TILE_SIZE)) / TILE_SIZE);
          int y = floor((currShape.vec.y + (j * TILE_SIZE)) / TILE_SIZE);
          if (x < 0 || y < 0) {
            state = GameState::GAMEOVER;
            return;
          }
        }
      }
    }
  }
}

void Game::handleShape() {
  if (currShape.exhausted) {
    Shape newShape = Shape();
    currShape = std::move(nextShape);
    nextShape = std::move(newShape);
  }
}

void Game::drawState(string str) {
  DrawText(str.c_str(), screenWidth / 2 - (str.size() * screenHeight / 64),
           screenHeight / 2, screenHeight / 16, BTN_COLOR);
}

void Game::drawScore() {
  string num = to_string(score);
  string zeroes = "000000000";
  for (size_t i = 0; i < num.size(); i++)
    zeroes.pop_back();
  string scoreText = zeroes + num;
  int x = screenWidth + floor(TILE_SIZE / 2) - uiMargin;
  int y = TILE_SIZE;
  DrawText(scoreText.c_str(), x, y, TILE_SIZE, WHITE);
}

void Game::drawNextShape() {
  Shape displayShape = nextShape;
  displayShape.vec.x = screenWidth - uiMargin;
  displayShape.vec.y = floor(screenHeight / 2 - 3 * TILE_SIZE);
  displayShape.draw();
}

void Game::draw() {
  switch (state) {
  case MENU:
    start.draw();
    exit.draw();
    break;
  case RUNNING:
    drawScore();
    drawNextShape();
    grid.draw();
    currShape.draw();
    paused.draw();
    break;
  case PAUSED:
    drawState("GAME PAUSED !");
    resume.draw();
    break;
  case GAMEOVER:
    drawState("GAME OVER !");
    restart.draw();
    break;
  }
}
