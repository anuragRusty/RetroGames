#include "grid.hpp"
#include "cell.hpp"
#include <cmath>
#include <cstddef>
#include <raylib.h>
#include <utility>

Grid::Grid() {
  for (size_t i = 0; i < ROWS; i++) {
    std::vector<Cell> row;
    for (size_t j = 0; j < COLS; j++) {
      Cell cell = Cell(j, i);
      row.push_back(std::move(cell));
    }
    matrix.push_back(std::move(row));
  }
}

void Grid::update(size_t &score) { removeRow(score); }

void Grid::removeRow(size_t &score) {
  for (size_t i = 0; i < ROWS; i++) {
    bool rowFilled = true;
    for (size_t j = 0; j < COLS; j++) {
      if (!matrix[i][j].exist) {
        rowFilled = false;
        break;
      }
    }
    if (rowFilled) {
      for (size_t k = 0; k < COLS; k++) {
        matrix[i][k].exist = false;
      }
      rotateRowUp(i);
      score += 100;
    }
  }
}

void Grid::rotateRowUp(size_t row) {
  for (size_t i = row; i >= 1; i--) {
    for (size_t j = 0; j < COLS; j++) {
      Cell &currCell = matrix[i][j];
      Cell &upCell = matrix[i - 1][j];
      currCell.exist = upCell.exist;
      currCell.color = upCell.color;
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
