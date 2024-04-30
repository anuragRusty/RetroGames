#include "player.cpp"
#include <cmath>
#include <raylib.h>
#include <vector>

const Rectangle BGsrc = Rectangle{0, 16, 800, 800};
const Rectangle BGdest = Rectangle{0, 0, BGsrc.width, BGsrc.height};

enum GameState {
  MENU,
  RUNNING,
  PAUSED,
  GAMEOVER,
};

class Game {
private:
  std::vector<Enemy> enemies;
  int level = 1;

public:
  float screenWidth = 800;
  float screenHeight = 800;
  Player player = Player(screenWidth / 2, screenHeight - 80, 5);

  void spawnEnemy() {
    if (enemies.size() == 0) {
      for (size_t i = 1; i < level + 1; i++) {
        for (size_t j = 0; j < 10; j++) {
          Enemy enemy = Enemy(j * 5 * 16, i * 5 * 16, 5);
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

  Game() { spawnEnemy(); }

  void update(float dt) {
    for (Enemy &enemy : enemies) {
      enemy.update(dt, screenHeight);
    }
    removeEnemy();
    player.update(dt, screenWidth, enemies);
    spawnEnemy();
  }

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, BGsrc, BGdest, Vector2{0, 0}, 0, WHITE);
    player.draw(texture);
    for (Enemy &enemy : enemies) {
      enemy.draw(texture);
    }
  }
};
