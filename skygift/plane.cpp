#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>

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

  Plane(float size, float spd) {
    planeDest = Rectangle{size, size, size, size};
    speed = spd;
  }

  void update(float dt, float screenWidth) {
    if (planeDest.x > (screenWidth - planeDest.width)) {
      dir = LEFT;
    } else if (planeDest.x < 0) {
      dir = RIGHT;
    }
    planeDest.x += speed * dir * dt;
  }

  void draw(Texture2D &texture) {
    switch (dir) {
    case LEFT:
      DrawTexturePro(texture, planeSrcLeft, planeDest, Vector2{0, 0}, 0, WHITE);
      break;
    case RIGHT:
      DrawTexturePro(texture, planeSrcRight, planeDest, Vector2{0, 0}, 0,
                     WHITE);
      break;
    }
  }
};
