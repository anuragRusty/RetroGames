#include "food.hpp"

Food::Food(float size) {
  rec.x = 48 * 7;
  rec.y = 48 * 2;
  rec.width = size;
  rec.height = size;
}

void Food::update(int maxWidth, int maxHeight) {
  int rows = std::floor(maxWidth / rec.width);
  int cols = std::floor(maxHeight / rec.width);
  if (eaten) {
    rec.x = GetRandomValue(1, rows - 1) * rec.width;
    rec.y = GetRandomValue(1, cols - 1) * rec.width;
    eaten = false;
  }
}

void Food::draw() {
  DrawRectangleRec(rec, RED);
  DrawRectangleLinesEx(rec, rec.width / 16, BLACK);
}