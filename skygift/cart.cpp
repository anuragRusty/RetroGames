#include "../libs/anim8.cpp"
#include "gift.cpp"
#include "plane.cpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>
using namespace std;

const size_t MAX_GIFT_CART = 3;
const Rectangle cartSrc = Rectangle{0, 224, 64, 28};

class Cart {
public:
  ObjDir dir;
  float speed;
  Anim8 anim;
  size_t gift_count = 0;
  int score = 0;
  vector<Gift> gifts;

  Cart(float dest_x, float dest_y, float scale, float spd) {
    speed = spd;
    anim.init(cartSrc.width, cartSrc.height, 2, 0.10, cartSrc.x, cartSrc.y,
              dest_x, dest_y - (scale * cartSrc.height), scale);
    for (int i = 0; i < 3; i++) {
      float size = anim.dest_rec.width / 3;
      auto gift = Gift(dest_x + (i * size),
                       dest_y - (1.6 * anim.dest_rec.height), size);
      gifts.push_back(gift);
    }
  }

  void catchGift(Gift &gift) {
    bool collison = CheckCollisionRecs(gift.giftDest, anim.dest_rec);
    if (collison && !gift.exhausted) {
      gift.exhausted = collison;
      score++;
      if (score <= MAX_GIFT_CART) {
        gift_count = score;
      }
    }
  }

  void go(float dt) { anim.dest_rec.x += dt * speed * dir; }

  void control(float dt, float maxWidth) {
    if (IsKeyDown(KEY_LEFT) && anim.dest_rec.x > 0) {
      dir = LEFT;
      go(dt);
      anim.update(dt);
    } else if (IsKeyDown(KEY_RIGHT) && anim.dest_rec.x < maxWidth) {
      dir = RIGHT;
      go(dt);
      anim.update(dt);
    }
  }

  void update(float dt, float screenWidth, vector<Gift> &giftsVec) {
    control(dt, (screenWidth - anim.dest_rec.width));
    for (size_t i = 0; i < gifts.size(); i++) {
      gifts[i].giftDest.x = anim.dest_rec.x + (i * gifts[i].giftDest.width);
    }

    for (Gift &gft : giftsVec) {
      catchGift(gft);
    }
  }

  void draw(Texture2D &texture) {
    anim.draw(texture);
    for (size_t i = 0; i < gift_count; i++) {
      gifts[i].draw(texture, false);
    }
  }
};
