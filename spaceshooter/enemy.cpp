#include <raylib.h>

class Enemy {
private:
  Rectangle src = Rectangle{16, 0, 16, 16};
  int speed = 0;
  int fallTime = GetRandomValue(800, 3200);

  void go(float dt) {
    if (fallTime <= 0) {
      dest.y += speed * dt;
    } else {
      fallTime -= dt;
    }
  }

  void handleState(float maxHeight) {
    if (dest.y > maxHeight || health <= 0)
      dead = true;
  }

public:
  Rectangle dest;
  int health = 1;
  bool dead = false;

  Enemy(float x, float y, float scale) {
    int randIndex = GetRandomValue(1, 5);
    speed = (src.width * scale * (scale / 2)) - (src.width * randIndex);
    src.x *= randIndex;
    health = randIndex;
    dest = Rectangle{x, y, src.width * scale, src.height * scale};
  }

  void update(float dt, float maxHeight) {
    go(dt);
    handleState(maxHeight);
  }

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, WHITE);
  }
};
