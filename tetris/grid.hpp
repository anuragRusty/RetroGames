#ifndef GRID_H
#define GRID_H

#include <cstddef>
#define ROWS 20
#define COLS 10

#include "cell.hpp"
#include <raylib-cpp.hpp>
#include <vector>
using namespace std;

class Grid {
public:
  vector<vector<Cell>> matrix;
  Grid();
  void removeRow(size_t &score);
  void rotateRowUp(size_t row);
  void update(size_t &score);
  void draw();
};

#endif // !DEBUG
