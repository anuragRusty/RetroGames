#include "gift.hpp"

void Gift::go(float dt, int maxWidth) {
  paraDest.y += dt * y_speed;
  giftDest.y += dt * y_speed;

  if (paraDest.x > maxWidth || giftDest.x > maxWidth)
    x_speed = 0;
  if (paraDest.x <= 0 || giftDest.x <= 0)
    x_speed = 0;
  paraDest.x += dt * x_speed * dx;
  giftDest.x += dt * x_speed * dx;
}

void Gift::isExhausted(float screenHeight, int &life) {
  float maxHeight = screenHeight - (screenHeight / 6) - giftDest.height;
  if (giftDest.y > maxHeight && !exhausted) {
    exhausted = true;
    if (life > 0)
      life--;
  }
}

Gift::Gift(float x, float y, float size) {
  paraDest = Rectangle{x, y - size + (size / 10), size, size};
  giftDest = Rectangle{x, y, size, size};
}

void Gift::update(float dt, float screenHeight, float screenWidth, int &life) {
  isExhausted(screenHeight, life);
  go(dt, screenWidth - paraDest.width);
}

void Gift::draw(Texture2D &texture, bool paraShoot) {
  if (!exhausted) {
    if (paraShoot)
      DrawTexturePro(texture, paraSrc, paraDest, Vector2{0, 0}, 0, WHITE);
    DrawTexturePro(texture, gftSrc, giftDest, Vector2{0, 0}, 0, WHITE);
  }
}
