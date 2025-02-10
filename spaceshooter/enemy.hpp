#ifndef ENEMY_H
#define ENEMY_H

#include <raylib-cpp.hpp>

class Enemy {
private:
  Rectangle src = Rectangle{16, 0, 16, 16};
  int speed = 0;
  int fallTime = GetRandomValue(800, 3200);

  void go(float dt);
  void handleState(float maxHeight);

public:
  Rectangle dest;
  int health = 1;
  bool dead = false;

  Enemy(float x, float y, float scale);
  void update(float dt, float maxHeight);
  void draw(Texture2D &texture);
};

#endif