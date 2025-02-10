#ifndef SNAKE_H
#define SNAKE_H

#include "food.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <vector>

using namespace std;

enum DIR {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

class Snake {
public:
  DIR dir = DIR::RIGHT;
  bool biten = false;
  float upTime = 0;
  std::vector<Rectangle> segments;

  Snake(float x, float y, float size);
  void update(float dt, Food &food, int maxWidth, int maxHeight);
  void eat(Food &food);
  void expand();
  void updateSegments();
  void go(int maxWidth, int maxHeight);
  void control();
  void resetGame();
  void draw();
};

#endif