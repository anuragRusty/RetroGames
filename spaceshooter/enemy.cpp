#include "enemy.hpp"

void Enemy::go(float dt) {
  if (fallTime <= 0) {
    dest.y += speed * dt;
  } else {
    fallTime -= dt;
  }
}

void Enemy::handleState(float maxHeight) {
  if (dest.y > maxHeight || health <= 0)
    dead = true;
}

Enemy::Enemy(float x, float y, float scale) {
  int randIndex = GetRandomValue(1, 5);
  speed = (src.width * scale * (scale / 2)) - (src.width * randIndex);
  src.x *= randIndex;
  health = randIndex;
  dest = Rectangle{x, y, src.width * scale, src.height * scale};
}

void Enemy::update(float dt, float maxHeight) {
  go(dt);
  handleState(maxHeight);
}

void Enemy::draw(Texture2D &texture) {
  DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, WHITE);
}