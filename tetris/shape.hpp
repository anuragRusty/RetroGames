#ifndef SHAPE_H
#define SHAPE_H

#include <raylib.hpp>

class Shape {
public:
  bool sprite[4][4];
  Vector2 vec;
  Color color;
  bool collided = false;

  Shape();
  void checkCollison();
  void controlLeftRight();
  void goDown();
  void rotate();
  void update();
  void draw();
};

#endif // DEBUG
