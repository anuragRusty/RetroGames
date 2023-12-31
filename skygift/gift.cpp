#include <iostream>
#include <raylib.h>
using namespace std;

const Rectangle gftSrc = Rectangle{0, 64, 32, 32};
const Rectangle paraSrc = Rectangle{0, 32, 32, 32};

class Gift {
public:
  Rectangle giftDest;
  bool exhausted = false;

private:
  Rectangle paraDest;
  float dx = GetRandomValue(-1, 2);
  float dy = 1;
  float y_speed = GetRandomValue(100, 160);
  float x_speed = GetRandomValue(100, 240);

  void go(float dt, int maxWidth) {
    paraDest.y += dt * y_speed;
    giftDest.y += dt * y_speed;

    if (paraDest.x > maxWidth || giftDest.x > maxWidth)
      x_speed = 0;

    if (paraDest.x <= 0 || giftDest.x <= 0)
      x_speed = 0;

    paraDest.x += dt * x_speed * dx;
    giftDest.x += dt * x_speed * dx;
  }

  void isExhausted(float screenHeight, int &life) {
    float maxHeight = screenHeight - (screenHeight / 6) - giftDest.height;
    if (giftDest.y > maxHeight && !exhausted) {
      exhausted = true;
      if (life > 0)
        life--;
    }
  }

public:
  Gift(float x, float y, float size) {
    paraDest = Rectangle{x, y - size + (size / 10), size, size};
    giftDest = Rectangle{x, y, size, size};
  }

  void update(float dt, float screenHeight, float screenWidth, int &life) {
    isExhausted(screenHeight, life);
    go(dt, screenWidth - paraDest.width);
  }

  void draw(Texture2D &texture, bool paraShoot) {
    if (!exhausted) {
      if (paraShoot)
        DrawTexturePro(texture, paraSrc, paraDest, Vector2{0, 0}, 0, WHITE);
      DrawTexturePro(texture, gftSrc, giftDest, Vector2{0, 0}, 0, WHITE);
    }
  }
};
