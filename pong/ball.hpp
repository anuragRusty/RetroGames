#ifndef BALLS_H
#define BALLS_H

#include <raylib-cpp.hpp>

class Ball {
public:
  Vector2 vec;
  float radius;
  float speed;
  int dx = 1;
  int dy = 1;

  Ball(float r, float spd, float maxWidth, float maxHeight);
  void update(float dt, Rectangle playerRec, Rectangle playerRec2, int maxWidth,int maxHeight);
  void go(float dt);
  void bounce(Rectangle playerRec, Rectangle playerRec2, int maxWidth,int maxHeight);
  void draw();
};

#endif
