#include "../libs/anim8.cpp"
#include "plane.cpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
using namespace std;

const Rectangle cartSrc = Rectangle{0, 224, 64, 28};
const Rectangle cartSrc2 = Rectangle{64, 224, 64, 28};

class Cart {
  ObjDir dir;

  void update(float dt, float screenWidth) {}

  void draw(Texture2D &texture) {}
};
