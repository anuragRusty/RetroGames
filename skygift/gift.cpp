#include <iostream>
#include <raylib.h>
using namespace std;

const Rectangle gftSrc = Rectangle{0, 64, 32, 32};
const Rectangle paraSrc = Rectangle{0, 32, 32, 32};

class Gift {
public:
  Rectangle giftDest;
  Rectangle paraDest;
  float dx = GetRandomValue(-1, 1);
  float dy = 1;
  float speed = GetRandomValue(200, 250);
  bool exhausted = false;

  Gift(float x, float y, float size) {
    paraDest = Rectangle{x, y - size + (size / 10), size, size};
    giftDest = Rectangle{x, y, size, size};
  }

  void go(float dt) {
    paraDest.y += dt * speed;
    giftDest.y += dt * speed;
    paraDest.x += dt * speed * dx;
    giftDest.x += dt * speed * dx;
  }

  void isExhausted(float screenHeight) {
    float maxHeight = screenHeight - (screenHeight / 6) - giftDest.height;
    exhausted = giftDest.y > maxHeight;
  }

  void update(float dt, float screenHeight) {
    isExhausted(screenHeight);
    go(dt);
  }

  void draw(Texture2D &texture) {
    if (exhausted)
      cout << "EXHAUSTED" << endl;
    DrawTexturePro(texture, paraSrc, paraDest, Vector2{0, 0}, 0, WHITE);
    DrawTexturePro(texture, gftSrc, giftDest, Vector2{0, 0}, 0, WHITE);
  }
};
