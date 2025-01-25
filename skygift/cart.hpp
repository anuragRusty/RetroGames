#ifndef CART_H
#define CART_H

#include "../include/anim8.hpp"
#include "gift.hpp"
#include "plane.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <vector>

using namespace std;

const size_t MAX_GIFT_CART = 3;
const Rectangle cartSrc = Rectangle{0, 224, 64, 28};

class Cart {
public:
  size_t score = 0;

private:
  ObjDir dir;
  float speed;
  Anim8 anim;
  size_t gift_count = 0;
  vector<Gift> gifts;

  void catchGift(Gift &gift);
  void go(float dt);
  void control(float dt, float maxWidth);
public:
  Cart(float dest_x, float dest_y, float scale, float spd);
  void update(float dt, float screenWidth, vector<Gift> &giftsVec);
  void draw(Texture2D &texture);
};

#endif