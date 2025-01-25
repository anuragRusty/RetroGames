#include "plane.hpp"

Plane::Plane(float size, float spd) {
  planeDest = Rectangle{size, size, size, size};
  speed = spd;
}

void Plane::update(float dt, float screenWidth) {
  if (planeDest.x > (screenWidth - planeDest.width)) {
      dir = LEFT;
  }else if (planeDest.x < 0) {
      dir = RIGHT;
  }
  planeDest.x += speed * dir * dt;
}

void Plane::draw(Texture2D &texture) {
  switch (dir) {
    case LEFT:
      DrawTexturePro(texture, planeSrcLeft, planeDest, Vector2{0, 0}, 0, WHITE);
      break;
    case RIGHT:
      DrawTexturePro(texture, planeSrcRight, planeDest, Vector2{0, 0}, 0,WHITE);
      break;
  }
}
