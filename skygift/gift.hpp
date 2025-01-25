#ifndef GIFT_H
#define GIFT_H

#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

const Rectangle gftSrc = Rectangle{0, 64, 32, 32};
const Rectangle paraSrc = Rectangle{0, 32, 32, 32};

class Gift {
public:
  Rectangle giftDest;
  bool exhausted = false;

private:
  Rectangle paraDest;
  float dx = GetRandomValue(-1, 2);
  float dy = 1;
  float y_speed = GetRandomValue(100, 160);
  float x_speed = GetRandomValue(100, 240);

  void go(float dt, int maxWidth);
  void isExhausted(float screenHeight, int &life);

public:
  Gift(float x, float y, float size);
  void update(float dt, float screenHeight, float screenWidth, int &life);
  void draw(Texture2D &texture, bool paraShoot);
};

#endif