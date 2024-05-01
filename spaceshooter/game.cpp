#include "../libs/button.cpp"
#include "player.cpp"
#include <functional>
#include <raylib.h>
#include <string>
#include <vector>

const Rectangle BGsrc = Rectangle{0, 16, 800, 800};
const Rectangle BGdest = Rectangle{0, 0, BGsrc.width, BGsrc.height};
const int TILE_SIZE = 16;
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
  float scale = 5;

  Game() { spawnEnemy(); }

  void update(float dt) {
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

  void draw(Texture2D &texture) {
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
      DrawText(("Level " + std::to_string(level)).c_str(),
               screenWidth / 2 - (screenWidth / 10), screenHeight / 32,
               screenWidth / 20, WHITE);
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

private:
  std::vector<Enemy> enemies;
  Player player = Player(screenWidth / 2, screenHeight - (screenHeight / 10),
                         scale, screenWidth);
  size_t level = 0;
  GameState state = MENU;
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

  void drawState(string str) {
    DrawText(str.c_str(), screenWidth / 2 - (str.size() * screenHeight / 32),
             screenHeight / 2, screenHeight / 16, BTN_COLOR);
  }

  void spawnEnemy() {
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

  void removeEnemy() {
    for (size_t i = 0; i < enemies.size(); i++) {
      if (enemies[i].dead)
        enemies.erase(enemies.begin() + i);
    }
  }

  void resetGame() {
    level = 0;
    player.score = 0;
  }
};
