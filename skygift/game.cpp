#include "../libs/button.cpp"
#include "background.cpp"
#include "cart.cpp"
#include <functional>
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>

using namespace std;

const Color BTN_COLOR = WHITE;

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

private:
  int life = 3;
  Button start = Button(screenWidth / 3, screenHeight / 3, screenHeight / 16,
                        "START", BTN_COLOR);
  Button exit = Button(screenWidth / 3, screenHeight / 3 + (screenHeight / 16),
                       screenHeight / 16, "EXIT", BTN_COLOR);
  Button paused = Button(screenWidth - (6 * 1.3 * (screenHeight / 16)),
                         screenHeight - (screenHeight / 16), screenHeight / 16,
                         "PAUSED", BTN_COLOR);
  Button restart = Button(screenWidth - (7 * 1.3 * (screenHeight / 16)),
                          screenHeight - (screenHeight / 16), screenHeight / 16,
                          "RESTART", BTN_COLOR);
  Button resume = Button(screenWidth - (6 * 1.3 * (screenHeight / 16)),
                         screenHeight - (screenHeight / 16), screenHeight / 16,
                         "RESUME", BTN_COLOR);
  GameState state = MENU;
  Background background = Background(screenWidth, screenHeight);
  Cart cart = Cart((screenHeight / 6), screenHeight - (screenHeight / 6),
                   screenHeight / 400, 200);
  Plane plane = Plane(screenHeight / 6, 300);
  vector<Gift> gifts;

  void spawnGift() {
    auto rand = GetRandomValue(0, 130);
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

  void resetGame() {
    cart = Cart((screenHeight / 6), screenHeight - (screenHeight / 6), 2, 200);
    plane = Plane(screenHeight / 6, 300);
    life = 3;
    while (!gifts.empty())
      gifts.pop_back();
  }

  void updateGifts(float &dt) {
    for (Gift &gift : gifts) {
      gift.update(dt, screenHeight, screenWidth, life);
    }
  }

  void drawState(string str) {
    DrawText(str.c_str(), screenWidth / 2 - (str.size() * screenHeight / 32),
             screenHeight / 2, screenHeight / 16, BTN_COLOR);
  }

  void drawGifts(Texture2D &texture) {
    for (Gift &gift : gifts) {
      gift.draw(texture, true);
    }
  }

public:
  void update(float dt) {
    function<void()> handle_start = [&]() { state = GameState::RUNNING; };
    function<void()> handle_paused = [&]() { state = GameState::PAUSED; };
    function<void()> handle_exit = []() { CloseWindow(); };
    function<void()> handle_restart = [&]() {
      resetGame();
      handle_start();
    };

    switch (state) {
    case MENU:
      start.onClick(handle_start);
      exit.onClick(handle_exit);
      break;
    case RUNNING:
      background.update(cart.score, life);
      plane.update(dt, screenWidth);
      cart.update(dt, screenWidth, gifts);
      paused.onClick(handle_paused);
      spawnGift();
      removeGift();
      updateGifts(dt);
      if (life <= 0)
        state = GameState::GAMEOVER;
      break;
    case PAUSED:
      resume.onClick(handle_start);
      break;
    case GAMEOVER:
      restart.onClick(handle_restart);
      break;
    }
  }

  void draw(Texture2D &texture) {
    background.draw(texture);
    switch (state) {
    case MENU:
      start.draw();
      exit.draw();
      break;
    case RUNNING:
      plane.draw(texture);
      cart.draw(texture);
      drawGifts(texture);
      paused.draw();
      break;
    case PAUSED:
      drawState("GAME PAUSED !");
      resume.draw();
      break;
    case GAMEOVER:
      drawState("GAME OVER !");
      restart.draw();
      break;
    }
  }
};
