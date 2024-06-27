#include "game.hpp"
#include "cell.hpp"
#include "shape.hpp"
#include <raylib.h>
#include <string>

void Game::update(float dt) {
  currShape.update(dt, grid);
  handleShape();
  grid.update(score);
}

void Game::handleShape() {
  if (currShape.exhausted) {
    currShape.insertShape(grid);
    Shape newShape = Shape();
    currShape = std::move(nextShape);
    nextShape = std::move(newShape);
  }
}

void Game::drawScore() {
  string num = to_string(score);
  string zeroes = "0000000";
  for (size_t i = 0; i < num.size(); i++)
    zeroes.pop_back();
  string scoreText = zeroes + num;
  int x = screenWidth + (TILE_SIZE / 2) - uiMargin;
  int y = screenHeight - TILE_SIZE;
  DrawText(scoreText.c_str(), x, y, TILE_SIZE, WHITE);
}

void Game::drawNextShape() {
  Shape displayShape = nextShape;
  displayShape.vec.x = screenWidth - uiMargin;
  displayShape.vec.y = floor(screenHeight / 2 - 3 * TILE_SIZE);
  displayShape.draw();
}

void Game::draw() {
  drawScore();
  drawNextShape();
  grid.draw();
  currShape.draw();
}
