#include "player.cpp"
#include <raylib.h>
#include <string>
#include <vector>

const Rectangle BGsrc = Rectangle{0, 16, 800, 800};
const Rectangle BGdest = Rectangle{0, 0, BGsrc.width, BGsrc.height};
const int TILE_SIZE = 16;

enum GameState {
  MENU,
  RUNNING,
  PAUSED,
  GAMEOVER,
};

class Game {
private:
  std::vector<Enemy> enemies;
  size_t level = 0;

public:
  float screenWidth = 800;
  float screenHeight = 800;
  float scale = 5;
  Player player = Player(screenWidth / 2, screenHeight - (screenHeight / 10),
                         scale, screenWidth);

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
    DrawText(("Level " + std::to_string(level)).c_str(),
             screenWidth / 2 - (screenWidth / 10), screenHeight / 32,
             screenWidth / 20, WHITE);
  }
};
