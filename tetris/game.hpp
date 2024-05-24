#ifndef GAME_H
#define GAME_H

#include "grid.hpp"
#include "shape.hpp"
#include <vector>

class Game {
private:
  Grid grid = Grid();
  std::vector<Shape> shapes;

public:
  void update(float dt);
  void draw();
  void removeShape();
};

#endif // !DEBUG
