#include "cell.hpp"

Cell::Cell(int x, int y) {
  rec.x = x * TILE_SIZE;
  rec.y = y * TILE_SIZE;
}

void Cell::draw() const {
  if (exist)
    DrawRectangleRec(rec, color);
}

void Cell::setPosAndClr(int x, int y, Color clr) {
  rec.x = x;
  rec.y = y;
  color = clr;
}

Vector2 Cell::getPosIndex() const {
  return Vector2{rec.x / TILE_SIZE, rec.y / TILE_SIZE};
}
