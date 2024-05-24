#include "shape.hpp"
#include "sprites.hpp"
#include <raylib-cpp.hpp>

Color colors[7] = {RED, YELLOW, GREEN, BLUE, VIOLET, ORANGE, WHITE};

Shape::Shape() {
  int randomSpritIndex = GetRandomValue(0, 7);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      sprite[i][j] = SPRITES_ARRAY[randomSpritIndex][i][j];
    }
  }
}
