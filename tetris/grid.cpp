#include "grid.hpp"

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

Grid::Grid() {
  for (std::size_t i = 0; i < 20; i++) {
    std::vector<Cell> newRow;
    matrix.push_back(newRow);
    for (std::size_t j = 0; j < 10; j++) {
      Cell newCell(i, j);
      matrix[0].push_back(newCell);
    }
  }
}

void Grid::draw() {
  for (const auto &row : matrix) {
    for (const auto &cell : row) {
      cell.draw();
    }
  }
}
