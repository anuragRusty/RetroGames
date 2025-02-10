#include "bullet.hpp"

Bullet::Bullet(float x, float y, float scale) {
   rec = Rectangle{x - (1 * scale), y, 2 * scale, 4 * scale};
}

void Bullet::go(float dt) { 
   rec.y -= speed * dt; 
}
  
void Bullet::checkForHitExhaustion(Enemy &enemy, size_t &score) {
  if (rec.y < 0)
    exhausted = true;
  if (CheckCollisionRecs(rec, enemy.dest)) {
    exhausted = true;
    enemy.health -= 1;
    score++;
   }
}

void Bullet::update(float dt, std::vector<Enemy> &enemies, size_t &score) {
   go(dt);
   for (Enemy &enemy : enemies)
     checkForHitExhaustion(enemy, score);
}

void Bullet::draw() { 
    DrawRectangleRec(rec, RED);
 }