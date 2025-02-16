#ifndef FOOD_H
#define FOOD_H

#include <raylib-cpp.hpp>
#include <raymath.h>

class Food {
public:
  bool eaten = false;
  Rectangle rec;

  Food(float size);
  void update(int maxWidth, int maxHeight);
  void draw(const Texture2D &texture);
};

#endif