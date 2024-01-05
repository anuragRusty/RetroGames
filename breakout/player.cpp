#include <cmath>
#include <cstddef>
#include <raylib.h>

const Rectangle playerSrc = Rectangle{0, 32, 32, 12};

enum HorizontalSide {
  LEFT = -1,
  STILL = 0,
  RIGHT = 1,
};

class Player {
private:
  float speed = 0;
  float maxWidth = 0;
  HorizontalSide dx;

  void go(float dt) {
    dest.x += speed * dt * dx;
    leftDest.x = dest.x;
    midDest.x = dest.x + dest.width / std::sqrt(6);
    rightDest.x = dest.x + (dest.width - dest.width / 8);
  }

public:
  int life = 3;
  int score = 0;
  Rectangle dest;
  Rectangle leftDest;
  Rectangle midDest;
  Rectangle rightDest;

  Player(float screenWidth, float screenHeight, float scale, float spd) {
    dest.width = playerSrc.width * scale * 1.35;
    dest.height = playerSrc.height * scale;
    dest.x = (screenWidth / 2) - playerSrc.width * scale;
    dest.y = screenHeight - playerSrc.height * scale;
    speed = spd;
    maxWidth = screenWidth - dest.width;
    leftDest = Rectangle{dest.x, dest.y, dest.width / 8, dest.height};
    midDest =
        Rectangle{dest.x + dest.width / 2, dest.y, dest.width / 6, dest.height};
    rightDest = Rectangle{dest.x + (dest.width - dest.width / 8), dest.y,
                          dest.width / 8, dest.height};
  }

  void update(float dt) {
    if (IsKeyDown(KEY_LEFT) && dest.x >= 0) {
      dx = HorizontalSide::LEFT;
    } else if (IsKeyDown(KEY_RIGHT) && dest.x <= maxWidth) {
      dx = HorizontalSide::RIGHT;
    } else {
      dx = HorizontalSide::STILL;
    }
    go(dt);
  }

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, playerSrc, dest, Vector2{0, 0}, 0, WHITE);
  }
};
