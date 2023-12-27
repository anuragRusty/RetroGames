#include <raylib-cpp.hpp>
#include <raylib.h>

class Ball {
public:
  Vector2 vec;
  float radius;
  float speed;
  int dx = 1;
  int dy = 1;

  Ball(float r, float spd, float maxWidth, float maxHeight) {
    speed = spd;
    radius = r;
    vec.x = maxWidth / 4;
    vec.y = maxHeight / 2;
  }

  void update(float dt, Rectangle playerRec, Rectangle playerRec2, int maxWidth,
              int maxHeight) {
    go(dt);
    bounce(playerRec, playerRec2, maxWidth, maxHeight);
  }

  void go(float dt) {
    vec.x += dt * speed * dx;
    vec.y += dt * speed * dy;
  }

  void bounce(Rectangle playerRec, Rectangle playerRec2, int maxWidth,
              int maxHeight) {
    if (vec.x > (maxWidth - radius)) {
      dx = -1;
    } else if (vec.x < radius) {
      dx = 1;
    }

    if (vec.y > (maxHeight - radius)) {
      dy = -1;
    } else if (vec.y < radius) {
      dy = 1;
    }

    if (CheckCollisionCircleRec(vec, radius, playerRec) ||
        CheckCollisionCircleRec(vec, radius, playerRec2)) {
      dx = -dx;
    }
  }

  void draw() { DrawCircleV(vec, radius, GREEN); }
};
