#include "game.hpp"

void Game::spawnGift() {
  auto rand = GetRandomValue(0, 130);
  if (rand == 1) {
    Gift gft = Gift(plane.planeDest.x, plane.planeDest.y, screenHeight / 16);
    gifts.push_back(gft);
  }
}

void Game::removeGift() {
  for (size_t i = 0; i < gifts.size(); i++) {
     if (gifts[i].exhausted) {
        gifts.erase(gifts.begin() + i);
    }
  }
}

void Game::resetGame() {
  cart = Cart((screenHeight / 6), screenHeight - (screenHeight / 6), 2, 200);
  plane = Plane(screenHeight / 6, 300);
  life = 3;
  while (!gifts.empty())
    gifts.pop_back();
}

void Game::updateGifts(float &dt) {
  for (Gift &gift : gifts) {
    gift.update(dt, screenHeight, screenWidth, life);
  }
}

void Game::drawState(string str) {
  DrawText(str.c_str(), screenWidth / 2 - (str.size() * screenHeight / 32),screenHeight / 2, screenHeight / 16, BTN_COLOR);
}

void Game::drawGifts(Texture2D &texture) {
  for (Gift &gift : gifts) {
    gift.draw(texture, true);
  }
}

void Game::update(float dt) {
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

void Game::draw(Texture2D &texture) {
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
