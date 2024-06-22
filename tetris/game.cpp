#include "game.hpp"
#include "shape.hpp"
#include <iostream>

void Game::update(float dt) {
  spawnShape();
  removeShape();
  for (Shape &shape : shapes)
    shape.update(dt);
}

void Game::spawnShape() {
  if (shapes.empty()) {
    Shape newShape = Shape();
    shapes.push_back(newShape);
  }
  std::cout << shapes.size() << "\n";
}

void Game::removeShape() {
  size_t i = 0;
  for (Shape &shape : shapes) {
    if (shape.collided) {
      shapes.erase(shapes.begin() + i);
    }
    i++;
  }
}

void Game::draw() {
  grid.draw();
  for (Shape &shape : shapes)
    shape.draw();
}
