#ifndef GRID_H
#define GRID_H

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
  void update(float dt);
  void draw();
};

#endif // !DEBUG
