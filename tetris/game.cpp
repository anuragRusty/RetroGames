#include "game.hpp"
#include "cell.hpp"
#include "shape.hpp"
#include <raylib.h>
#include <string>

void Game::update(float dt) {
  spawnShape();
  // removeShape();
  shapes[0].update(dt, grid);
}

void Game::spawnShape() {
  if (shapes.size() < 2) {
    Shape newShape = Shape();
    shapes.push_back(newShape);
  }
}

void Game::removeShape() {
  size_t i = 0;
  if (shapes[0].exhausted)
    shapes.erase(shapes.begin() + 0);
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
  Shape nextShape = shapes[shapes.size() - 1];
  nextShape.vec.x = screenWidth - uiMargin;
  nextShape.vec.y = floor(screenHeight / 2 - 3 * TILE_SIZE);
  nextShape.draw();
}

void Game::draw() {
  drawScore();
  drawNextShape();
  grid.draw();
  shapes[0].draw();
}
