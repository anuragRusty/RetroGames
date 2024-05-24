#ifndef GRID_H
#define GRID_H
#define TILE_SIZE 40
#define ROWS 20;
#define COLS 10;
#include <raylib.h>
#include <raylib.hpp>
#include <vector>

class Cell {
public:
  Rectangle rec = {0, -TILE_SIZE, TILE_SIZE, TILE_SIZE};
  bool exist = false;
  Color color = WHITE;

  void update(float dt) {}

  void draw() const;

  Cell(int x, int y);

  void setPosAndClr(int x, int y, Color clr);

  Vector2 getPosIndex() const;
};

class Grid {
public:
  std::vector<std::vector<Cell>> matrix;
  Grid();
  void update(float dt);
  void draw();
};

#endif // !DEBUG
