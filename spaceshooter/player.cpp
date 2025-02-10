#include "player.hpp"

void Player::applyAccelration(float dt) {
  if (speed < maxSpeed) {
    speed += accelaration * dt;
  } else {
    speed = maxSpeed;
  }
}
void Player::applyFriction(float dt) {
  if (speed > 0) {
    speed -= friction * dt;
  } else {
    speed = Side::STILL;
  }
}

void Player::go(float dt) { 
  dest.x += speed * dx * dt; 
}

void Player::shoot(float dt) {
  if (lTime > loadDelay && IsKeyDown(KEY_SPACE)) {
    Bullet bullet = Bullet(dest.x + (dest.width / 2),
                           dest.y - dest.height / 3, dest.width / 16);
    bullets.push_back(bullet);
    lTime = 0;
  }
  lTime += dt;
}

void Player::tinting(float dt) {
  Color colors[2] = {RED, WHITE};
  if (state == State::HIT && tTimeDur > 0) {
    if (tTime > loadDelay) {
      color = colors[tCount % 2];
      tCount++;
      tTime = 0;
    }
    tTime += dt;
    tTimeDur -= dt;
  } else if (state == State::HIT) {
    color = WHITE;
    state = State::IDEAL;
  }
}

void Player::control(float dt) {
  if (dest.x > 0 && IsKeyDown(KEY_LEFT)) {
    dx = Side::LEFT;
    applyAccelration(dt);
  } else if (dest.x <= (maxWidth - dest.width) && IsKeyDown(KEY_RIGHT)) {
    dx = Side::RIGHT;
    applyAccelration(dt);
  } else {
    applyFriction(dt);
  }
  shoot(dt);
}

void Player::handleState(std::vector<Enemy> &enemies) {
  for (Enemy &enemy : enemies)
    if (CheckCollisionRecs(enemy.dest, dest)) {
      state = State::HIT;
      tTimeDur = loadDelay * state;
      enemy.health -= 1;
      lifes -= 1;
    }

  if (lifes <= 0)
    state = State::DEAD;
}

Player::Player(float x, float y, float scale, int screenWidth) {
  lifes = 3;
  maxWidth = screenWidth;
  dest = Rectangle{x, y, src.width * scale, src.height * scale};
}

void Player::update(float dt, float maxWidth, std::vector<Enemy> &enemies) {
  control(dt);
  go(dt);
  tinting(dt);
  handleState(enemies);

  for (Bullet &bullet : bullets)
    bullet.update(dt, enemies, score);

  for (size_t i = 0; i < bullets.size(); i++)
    if (bullets[i].exhausted)
      bullets.erase(bullets.begin() + i);
}

void Player::draw(Texture2D &texture) {
  DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, color);
  for (Bullet &bullet : bullets) {
    bullet.draw();
  }
  DrawText(std::to_string(score).c_str(), dest.width / 4, 0, dest.width,WHITE);
  for (size_t i = 1; i <= lifes; i++) {
    DrawTexturePro(texture, heart_src,Rectangle{maxWidth - (dest.width * i), 0, dest.width, dest.height},Vector2{0, 0}, 0, WHITE);
  }
}