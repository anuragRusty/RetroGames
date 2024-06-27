#ifndef GAME_H
#define GAME_H

#include "grid.hpp"
#include "shape.hpp"

class Game {
private:
  Grid grid = Grid();
  Shape currShape = Shape();
  Shape nextShape = Shape();
  size_t score = 0;

public:
  size_t screenWidth = 600;
  size_t uiMargin = 200;
  size_t screenHeight = 800;

  void handleShape();
  void update(float dt);
  void drawScore();
  void drawNextShape();
  void draw();
};

#endif // !DEBUG
