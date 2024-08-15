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
  size_t randomSpritIndex = GetRandomValue(0, 6);
  size_t randomColorIndex = GetRandomValue(0, 5);
  sprite = SPRITES[randomSpritIndex];
  color = colors[randomColorIndex];
  vec.y = -TILE_SIZE * 4;
  vec.x = TILE_SIZE * floor(COLS / 4) + 1;
}

void Shape::update(float dt, Grid &grid) {
  updateExhaustion(grid);
  controlMove(grid);
  controlRotate(grid);
  insertShape(grid);
  go(dt);
}

void Shape::updateExhaustion(Grid const &grid) {
  if (!exhausted) {
    Vector2 dummyVec = vec;
    dummyVec.y += TILE_SIZE;
    for (size_t i = 0; i < sprite.size(); i++) {
      for (size_t j = 0; j < sprite[i].size(); j++) {
        if (sprite[i][j]) {
          int x = floor((dummyVec.x + (i * TILE_SIZE)) / TILE_SIZE);
          int y = floor((dummyVec.y + (j * TILE_SIZE)) / TILE_SIZE);
          if (y <= 0)
            continue;
          if (y >= ROWS || grid.matrix[y][x].exist) {
            exhausted = true;
            break;
          }
        }
      }
    }
  }
}

void Shape::insertShape(Grid &grid) {
  if (exhausted) {
    for (size_t i = 0; i < sprite.size(); i++) {
      for (size_t j = 0; j < sprite[i].size(); j++) {
        if (sprite[i][j]) {
          int x = floor((vec.x + (i * TILE_SIZE)) / TILE_SIZE);
          int y = floor((vec.y + (j * TILE_SIZE)) / TILE_SIZE);
          if (x < 0 || y < 0)
            break;
          grid.matrix[y][x].color = color;
          grid.matrix[y][x].exist = true;
        }
      }
    }
  }
}

bool Shape::checkCollison(Grid const &grid) {
  for (size_t i = 0; i < sprite.size(); i++) {
    for (size_t j = 0; j < sprite[i].size(); j++) {
      if (sprite[i][j]) {
        int x = floor((vec.x + (i * TILE_SIZE)) / TILE_SIZE);
        int y = floor((vec.y + (j * TILE_SIZE)) / TILE_SIZE);
        if (y < -4 || y >= ROWS)
          return true;
        if (x < 0 || x >= COLS)
          return true;
        if (y < 0 || x < 0)
          continue;
        if (grid.matrix[y][x].exist)
          return true;
      }
    }
  }
  return false;
}

bool Shape::isMovable(Grid const &grid, int dx) {
  Shape dummyShape = *this;
  dummyShape.vec.x += dx;
  return !dummyShape.checkCollison(grid);
}

bool Shape::isRotatable(Grid const &grid, bool antiClock) {
  Shape dummyShape = *this;
  dummyShape.rotate(antiClock);
  return !dummyShape.checkCollison(grid);
}

void Shape::go(float dt) {
  if (moveTime >= moveDelay && !exhausted) {
    vec.y += TILE_SIZE;
    moveTime = 0;
  }
  moveTime += dt;
}

void Shape::controlMove(Grid const &grid) {
  if (IsKeyPressed(KEY_LEFT) && isMovable(grid, -TILE_SIZE) && !exhausted) {
    vec.x -= TILE_SIZE;
  } else if (IsKeyPressed(KEY_RIGHT) && isMovable(grid, TILE_SIZE) &&
             !exhausted) {
    vec.x += TILE_SIZE;
  } else if (IsKeyPressed(KEY_SPACE) && !exhausted) {
    vec.y += TILE_SIZE;
  }
}

void Shape::controlRotate(Grid const &grid) {
  if (IsKeyPressed(KEY_UP) && isRotatable(grid, true) && !exhausted) {
    rotate(true);
  } else if (IsKeyPressed(KEY_DOWN) && isRotatable(grid, false) && !exhausted) {
    rotate(false);
  }
}

void Shape::rotate(bool antiClock) {
  size_t n = sprite.size();
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i; j < n; j++) {
      bool temp = sprite[i][j];
      sprite[i][j] = sprite[j][i];
      sprite[j][i] = temp;
    }
  }
  if (!antiClock) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n / 2; j++) {
        bool temp = sprite[i][j];
        sprite[i][j] = sprite[j][i];
        sprite[j][i] = temp;
      }
    }
  } else {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n / 2; j++) {
        bool temp = sprite[i][j];
        sprite[i][j] = sprite[j][i];
        sprite[j][i] = temp;
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
