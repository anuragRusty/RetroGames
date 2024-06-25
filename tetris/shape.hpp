#ifndef SHAPE_H
#define SHAPE_H
#include "grid.hpp"
#include <raylib-cpp.hpp>
#include <vector>
using namespace std;

class Shape {
public:
  vector<vector<bool>> sprite = vector<vector<bool>>(4, vector<bool>(0, 4));
  Vector2 vec;
  Color color;
  bool exhausted = false;
  float moveTime = 0;
  float moveDelay = 0.75;

  Shape();
  void update(float dt, Grid &grid);
  void insertShape(Grid &grid);
  bool checkCollison(Grid &grid);
  void go(float dt);
  bool isMovable(Grid &grid);
  void controlMove();
  bool isRotatable(Grid &grid);
  void controlRotate();
  void goDown(float dt);
  void rotate(bool antiClock);
  void adjustX();
  bool adjustY();
  void draw();
};

#endif // DEBUG
