#ifndef SHAPE_H
#define SHAPE_H
#include "grid.hpp"
#include <raylib-cpp.hpp>
#include <utility>

class Shape {
public:
  bool sprite[4][4];
  Vector2 vec;
  Color color;
  bool collided = false;
  float moveTime = 0;
  float moveDelay = 0.75;

  Shape();
  void update(float dt);
  std::pair<bool, bool> checkCollison(Grid const &grid);
  void go(float dt);
  void controlMove();
  void controlRotate();
  void goDown(float dt);
  void rotate(bool antiClock);
  void adjustX();
  bool adjustY();
  void draw();
};

#endif // DEBUG
