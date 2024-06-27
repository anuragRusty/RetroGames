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
  void updateExhaustion(Grid const &grid);
  bool isMovable(Grid const &grid, int dx);
  bool isRotatable(Grid const &grid, bool antiClock);
  bool checkCollison(Grid const &grid);
  void controlRotate(Grid const &grid);
  void controlMove(Grid const &grid);
  void go(float dt);
  void goDown(float dt);
  void rotate(bool antiClock);
  void adjustX();
  bool adjustY();
  void draw();
};

#endif // DEBUG
