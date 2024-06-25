#include "grid.hpp"
#include "cell.hpp"
#include <cmath>
#include <raylib.h>

Grid::Grid() {
  for (std::size_t i = 0; i < COLS; i++) {
    std::vector<Cell> newRow;
    matrix.push_back(newRow);
    for (std::size_t j = 0; j < ROWS; j++) {
      Cell newCell(i, j);
      matrix[0].push_back(newCell);
    }
  }
}

void Grid::draw() {
  for (const auto &cells : matrix) {
    for (const auto &cell : cells) {
      cell.draw();
      DrawRectangleLinesEx(cell.rec, 1, WHITE);
    }
  }
}
