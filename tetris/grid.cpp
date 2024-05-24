#include "grid.hpp"

Grid::Grid() {
  for (std::size_t i = 0; i < ROWS; i++) {
    std::vector<Cell> newRow;
    matrix.push_back(newRow);
    for (std::size_t j = 0; j < COLS; j++) {
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
