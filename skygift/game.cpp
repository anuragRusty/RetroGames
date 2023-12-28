#include "background.cpp"
#include "cart.cpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>

using namespace std;

enum GameState {
  MENU,
  RUNNING,
  PAUSED,
  GAMEOVER,
};

class Game {
public:
  float screenWidth = 800;
  float screenHeight = 800;
  int life = 3;
  GameState state = MENU;
  Background background = Background(screenWidth, screenHeight);
  Cart cart =
      Cart((screenHeight / 6), screenHeight - (screenHeight / 6), 2, 200);
  Plane plane = Plane(screenHeight / 6, 300);
  vector<Gift> gifts;

  void spawnGift() {
    auto rand = GetRandomValue(0, 80);
    if (rand == 1) {
      Gift gft = Gift(plane.planeDest.x, plane.planeDest.y, screenHeight / 16);
      gifts.push_back(gft);
    }
  }

  void removeGift() {
    for (size_t i = 0; i < gifts.size(); i++) {
      if (gifts[i].exhausted) {
        gifts.erase(gifts.begin() + i);
      }
    }
  }

  void update(float dt) {
    background.update(cart.score, life);
    plane.update(dt, screenWidth);
    cart.update(dt, screenWidth);
    spawnGift();
    removeGift();
    for (Gift &gift : gifts) {
      cart.catchGift(gift);
      gift.update(dt, screenHeight, screenWidth, life);
    }
  }

  void draw(Texture2D &texture) {
    background.draw(texture);
    plane.draw(texture);
    cart.draw(texture);

    for (Gift &gift : gifts) {
      gift.draw(texture, true);
    }
  }
};
