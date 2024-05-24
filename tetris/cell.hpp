#ifndef CELL_H
#define CELL_H
#define TILE_SIZE 40
#include <raylib-cpp.hpp>

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

#endif // !CELL_H
