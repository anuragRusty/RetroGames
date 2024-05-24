#ifndef GRID_H
#define GRID_H
#define ROWS 20
#define COLS 20

#include "cell.hpp"
#include <raylib-cpp.hpp>
#include <vector>

class Grid {
public:
  std::vector<std::vector<Cell>> matrix;
  Grid();
  void update(float dt);
  void draw();
};

#endif // !DEBUG
