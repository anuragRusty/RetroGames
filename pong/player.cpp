#include "ball.cpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
using namespace std;

const Color colors[] = {RED, BLUE, YELLOW};

enum PlayerType {
  Player1 = 0,
  Player2 = 1,
  Computer = 2,
};

enum Dir {
  UP = -1,
  STILL = 0,
  DOWN = 1,
};

class Player {
public:
  Rectangle rec;
  float speed;
  PlayerType player;
  Color color;
  Dir dir = Dir::STILL;

  Player(PlayerType p, float spd, float size, float maxWidth, float maxHeight) {
    speed = spd;
    rec.width = size;
    rec.height = size * 3;
    rec.x = (p == 0 ? 0 : 1) * (maxWidth - rec.width);
    rec.y = maxHeight / 2 - rec.height;
    PlayerType player = p;
    color = colors[p];
  }

  void update(float dt, int maxWidth, int maxHeight, Ball &ball) {
    go(dt, maxWidth, maxHeight);
    control(ball, maxHeight);
  }

  void control(Ball &ball, int maxHeight) {
    switch (player) {
    case Player1:
      if (IsKeyDown(KEY_UP) && rec.y > 0) {
        dir = Dir::UP;
        cout << "FUCK" << endl;
      } else if (IsKeyDown(KEY_DOWN) && rec.y < (maxHeight - rec.height)) {
        dir = Dir::DOWN;
      } else {
        dir = Dir::STILL;
      }
      break;
    case Player2:
      if (IsKeyDown(KEY_W) && rec.y > 0) {
        dir = Dir::UP;
      } else if (IsKeyDown(KEY_DOWN) && rec.y < (maxHeight - rec.height)) {
        dir = Dir::DOWN;
      } else {
        dir = Dir::STILL;
      }
      break;
    case Computer:
      float mid_y = rec.y + rec.height / 2;
      if (ball.vec.y < mid_y && rec.y > 0) {
        dir = Dir::UP;
      } else if (ball.vec.y > mid_y && rec.y < (maxHeight - rec.height)) {
        dir = Dir::DOWN;
      } else {
        dir = Dir::STILL;
      }
      break;
    }
  }

  void go(float dt, int maxWidth, int maxHeight) { rec.y += dir * speed * dt; }

  void draw() { DrawRectangleRec(rec, color); }
};
