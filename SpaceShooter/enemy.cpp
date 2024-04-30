#include <raylib.h>

const Rectangle EnemySrc = Rectangle{16, 0, 16, 16};

class Enemy {
private:
  int speed = 200;
  int fallTime = GetRandomValue(800, 1000);

  void go(float dt) {
    if (fallTime <= 0) {
      dest.y += speed * dt;
    } else {
      fallTime -= dt;
    }
  }

  void handleState(float maxHeight) {
    if (dest.y > maxHeight)
      dead = true;
  }

public:
  Rectangle dest;
  int health = 1;
  bool dead = false;

  Enemy(float x, float y, float scale) {
    dest = Rectangle{x, y, EnemySrc.width * scale, EnemySrc.height * scale};
  }

  void update(float dt, float maxHeight) {
    go(dt);
    handleState(maxHeight);
  }

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, EnemySrc, dest, Vector2{0, 0}, 0, WHITE);
  }
};
