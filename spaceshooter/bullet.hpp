#ifndef BULLET_H
#define BULLET_H

#include <raylib-cpp.hpp>
#include "enemy.hpp"

class Bullet {
  private:
    Rectangle rec;
    float speed = 340;
  
    void go(float dt);
    void checkForHitExhaustion(Enemy &enemy, size_t &score);
  
    public:
      bool exhausted = false;
  
      Bullet(float x, float y, float scale);
      void update(float dt, std::vector<Enemy> &enemies, size_t &score);
      void draw();
};

#endif