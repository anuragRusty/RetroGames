#ifndef BALL_H
#define BALL_H

#include "ball.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
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

  Player(PlayerType p, float spd, float size, float maxWidth, float maxHeight);
  void update(float dt, int maxWidth, int maxHeight, Ball &ball);
  void control(Ball &ball, int maxHeight);
  void go(float dt, int maxWidth, int maxHeight);
  void draw();
};

#endif