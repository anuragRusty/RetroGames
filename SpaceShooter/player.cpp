#include "enemy.cpp"
#include <cstddef>
#include <iostream>
#include <raylib.h>
#include <vector>

const Rectangle PlayerSrc = Rectangle{0, 0, 16, 16};

enum Side {
  LEFT = -1,
  STILL = 0,
  RIGHT = 1,
};

class Bullet {
private:
  Rectangle rec;
  float speed = 340;

  void go(float dt) { rec.y -= speed * dt; }

  void checkExhaution(Enemy &enemy) {
    if (rec.y < 0) {
      exhausted = true;
    }
    if (CheckCollisionRecs(rec, enemy.dest)) {
      exhausted = true;
      enemy.dead = true;
    }
  }

public:
  bool exhausted = false;
  Bullet(float x, float y, float scale) {
    rec = Rectangle{x - (1 * scale), y, 2 * scale, 4 * scale};
  }

  void update(float dt, std::vector<Enemy> &enemies) {
    go(dt);
    for (Enemy &enemy : enemies)
      checkExhaution(enemy);
  }

  void draw() { DrawRectangleRec(rec, RED); }
};

class Player {
private:
  Rectangle dest;
  int maxSpeed = 280;
  int speed = 0;
  int accelaration = 1500;
  int friction = 1000;
  Side dx = Side::STILL;
  float lTime = 0;
  float tTime = 0;
  size_t tCount = 0;
  float loadDelay = 0.2;
  std::vector<Bullet> bullets;
  Color color = WHITE;

  void applyAccelration(float dt) {
    if (speed < maxSpeed) {
      speed += accelaration * dt;
    } else {
      speed = maxSpeed;
    }
  }
  void applyFriction(float dt) {
    if (speed > 0) {
      speed -= friction * dt;
    } else {
      speed = Side::STILL;
    }
  }

  void go(float dt) { dest.x += speed * dx * dt; }

  void shoot(float dt) {
    if (lTime > loadDelay && IsKeyDown(KEY_SPACE)) {
      Bullet bullet = Bullet(dest.x + (dest.width / 2),
                             dest.y - dest.height / 3, dest.width / 16);
      bullets.push_back(bullet);
      lTime = 0;
    }
    lTime += dt;
  }

  void tinting(float dt) {
    Color colors[2] = {RED, WHITE};
    if (tTime > loadDelay) {
      color = colors[tCount % 2];
      tCount++;
      tTime = 0;
    }
    tTime += dt;
  }

  void control(float dt, float maxWidth) {
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

public:
  int lifes = 3;

  Player(float x, float y, float scale) {
    lifes = 3;
    dest = Rectangle{x, y, PlayerSrc.width * scale, PlayerSrc.height * scale};
  }

  void update(float dt, float maxWidth, std::vector<Enemy> &enemies) {
    control(dt, maxWidth);
    go(dt);
    tinting(dt);

    for (Bullet &bullet : bullets) {
      bullet.update(dt, enemies);
    }

    for (size_t i = 0; i < bullets.size(); i++) {
      if (bullets[i].exhausted)
        bullets.erase(bullets.begin() + i);
    }
  }

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, PlayerSrc, dest, Vector2{0, 0}, 0, color);
    for (Bullet &bullet : bullets) {
      bullet.draw();
    }
  }
};
