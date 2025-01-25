#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

const Rectangle planeSrcRight = Rectangle{0, 160, 64, 64};
const Rectangle planeSrcLeft = Rectangle{64, 160, 64, 64};

enum ObjDir {
  LEFT = -1,
  RIGHT = 1,
};

class Plane {
private:
  float speed;
  ObjDir dir = LEFT;

public:
  Rectangle planeDest;

  Plane(float size, float spd);
  void update(float dt, float screenWidth);
  void draw(Texture2D &texture);
};

#endif
