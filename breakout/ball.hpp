#ifndef BALLS_H
#define BALLS_H

#include "grid.hpp"
#include "player.hpp"
#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

const Rectangle BallSrc = Rectangle{0, 0, 32, 32};

enum VerticalSide {
  TOP = -1,
  DOWN = 1,
};

class Ball {
private:
  float speed = 0;
  Rectangle dest;
  Vector2 vec;
  float maxWidth = 0;
  float maxHeight = 0;
  HorizontalSide dx = HorizontalSide::RIGHT;
  VerticalSide dy = VerticalSide::TOP;

  void go(float dt);
  void hitAndBounce(Grid &grid);
  void bounce(Player &player);
public:
  Ball(float screenWidth, float screenHeight, float scale, float spd);
  void update(float dt, Player &player, Grid &grid);
  void draw(Texture2D &texture);
};

#endif