#include "shape.hpp"
#include "cell.hpp"
#include "grid.hpp"
#include "sprites.hpp"
#include <cmath>
#include <cstddef>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <utility>

Color colors[7] = {RED, YELLOW, GREEN, BLUE, VIOLET, ORANGE};

Shape::Shape() {
  int randomSpritIndex = GetRandomValue(0, 7);
  int randomColorIndex = GetRandomValue(0, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      sprite[i][j] = SPRITES_ARRAY[randomSpritIndex][i][j];
    }
  }
  color = colors[randomColorIndex];
  vec.y = -TILE_SIZE * 2;
  vec.x = TILE_SIZE * floor(COLS / 4) + 1;
}

std::pair<bool, bool> Shape::checkCollison(Grid const &grid) {
  size_t px = vec.x / TILE_SIZE;
  size_t py = vec.y / TILE_SIZE;
  std::pair<bool, bool> left_right = std::make_pair(false, false);
  for (size_t i = 1; i < 3; i++) {
    for (size_t j = 1; j < 3; j++) {
      if (!sprite[i][j])
        continue;
      if (sprite[i][j]) {
        bool top = true, right = true, bottom = true, left = true;
        right = grid.matrix[px + i][py + (j + 1)].exist;
        bottom = grid.matrix[px + (i + 1)][py + j].exist;
        left = grid.matrix[px + i][py + (j - 1)].exist;
        if (!(top && left && right && bottom)) {
        }
      }
    }
  }
  return left_right;
}

void Shape::update(float dt) {
  go(dt);
  controlMove();
  controlRotate();
}

void Shape::go(float dt) {
  if (moveTime >= moveDelay) {
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
        DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, WHITE);
      }
    }
  }
}
