#include "shape.hpp"
#include "cell.hpp"
#include "grid.hpp"
#include "sprites.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <utility>

Color colors[7] = {RED, YELLOW, GREEN, BLUE, VIOLET, ORANGE};

Shape::Shape() {
  int randomSpritIndex = GetRandomValue(0, 7);
  int randomColorIndex = GetRandomValue(0, 5);
  sprite = SPRITES[randomSpritIndex];
  color = colors[randomColorIndex];
  vec.y = TILE_SIZE;
  vec.x = TILE_SIZE * floor(COLS / 4) + 1;
}

void Shape::update(float dt, Grid &grid) {
  go(dt);
  controlMove();
  controlRotate();
  insertShape(grid);
}

bool Shape::checkCollison(Grid &grid) {
  Vector2 dummyVec = vec;
  dummyVec.x += TILE_SIZE;
  dummyVec.y += TILE_SIZE;
  for (size_t i = 0; i < sprite.size(); i++) {
    for (size_t j = 0; j < sprite[0].size(); j++) {
      if (sprite[i][j]) {
        int x = floor((vec.x + (i * TILE_SIZE)) / TILE_SIZE);
        int y = floor((vec.y + (j * TILE_SIZE)) / TILE_SIZE);
        if (x <= 0 || x >= COLS)
          return true;
        if (y >= ROWS)
          return true;
        // if (grid.matrix[x][y].exist)
        // return true;
      }
    }
  }
  return false;
}

void Shape::insertShape(Grid &grid) {
  if (checkCollison(grid)) {
    for (size_t i = 0; i < sprite.size(); i++) {
      for (size_t j = 0; j < sprite[i].size(); j++) {
        if (sprite[i][j]) {
          int x = floor((vec.x + (i * TILE_SIZE)) / TILE_SIZE);
          int y = floor((vec.y + (j * TILE_SIZE)) / TILE_SIZE);
          grid.matrix[x][y].color = color;
          grid.matrix[x][y].exist = true;
        }
      }
    }
    exhausted = true;
  }
}

void Shape::go(float dt) {
  if (moveTime >= moveDelay && !exhausted) {
    vec.y += TILE_SIZE;
    moveTime = 0;
  }
  moveTime += dt;
}

void Shape::controlMove() {
  if (IsKeyPressed(KEY_LEFT)) {
    vec.x -= TILE_SIZE;
  } else if (IsKeyPressed(KEY_RIGHT)) {
    vec.x += TILE_SIZE;
  } else if (IsKeyPressed(KEY_SPACE)) {
    vec.y += TILE_SIZE;
  }
}

void Shape::controlRotate() {
  if (IsKeyPressed(KEY_UP)) {
    rotate(true);
  } else if (IsKeyPressed(KEY_DOWN)) {
    rotate(false);
  }
}

void Shape::rotate(bool antiClock) {
  size_t n = 4;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i; j < n; j++) {
      std::swap(sprite[i][j], sprite[j][i]);
    }
  }
  if (!antiClock) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n / 2; j++) {
        std::swap(sprite[i][j], sprite[i][n - j - 1]);
      }
    }
  } else {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n / 2; j++) {
        std::swap(sprite[j][i], sprite[j][n - i - 1]);
      }
    }
  }
}

void Shape::draw() {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      if (sprite[i][j]) {
        int x = vec.x + (i * TILE_SIZE);
        int y = vec.y + (j * TILE_SIZE);
        DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
        DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, BLACK);
      }
    }
  }
}
