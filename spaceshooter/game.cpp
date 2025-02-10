#include "game.hpp"

Game::Game() { 
  spawnEnemy(); 
}

void Game::update(float dt) {
  std::function<void()> handle_start = [&]() { state = GameState::RUNNING; };
  std::function<void()> handle_paused = [&]() { state = GameState::PAUSED; };
  std::function<void()> handle_exit = []() { CloseWindow(); };
  std::function<void()> handle_restart = [&]() {
    resetGame();
    handle_start();
  };
 switch (state) {
   case MENU:
     start.onClick(handle_start);
     exit.onClick(handle_exit);
     break;
   case RUNNING:
     paused.onClick(handle_paused);
    for (Enemy &enemy : enemies)
      enemy.update(dt, screenHeight);
    removeEnemy();
    player.update(dt, screenWidth, enemies);
    spawnEnemy();
    if (player.state == State::DEAD)
     state = GAMEOVER;
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
  DrawTexturePro(texture, BGsrc, BGdest, Vector2{0, 0}, 0, WHITE);
  switch (state) {
  case MENU:
    start.draw();
    exit.draw();
    break;
  case RUNNING:
    player.draw(texture);
    for (Enemy &enemy : enemies)
      enemy.draw(texture);
    DrawText(("Level " + std::to_string(level)).c_str(),screenWidth / 2 - (screenWidth / 10), screenHeight / 32,screenWidth / 20, WHITE);
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

void Game::drawState(string str) {
  DrawText(str.c_str(), screenWidth / 2 - (str.size() * screenHeight / 32),screenHeight / 2, screenHeight / 16, BTN_COLOR);
}

void Game::spawnEnemy() {
  if (enemies.size() == 0) {
    for (size_t i = 0; i <= level; i++) {
      for (size_t j = 0; j <= 10; j++) {
        Enemy enemy =
            Enemy(j * scale * TILE_SIZE, (i + 1) * scale * TILE_SIZE, scale);
        enemies.push_back(enemy);
      }
    }
    level += 1;
  }
}

void Game::removeEnemy() {
  for (size_t i = 0; i < enemies.size(); i++) {
    if (enemies[i].dead)
      enemies.erase(enemies.begin() + i);
  }
}

void Game::resetGame() {
  level = 0;
  player.score = 0;
}
