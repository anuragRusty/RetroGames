#include "enemy.cpp"
#include <cstddef>
#include <raylib.h>
#include <string>
#include <vector>

enum State {
  IDEAL = 0,
  HIT = 10,
  DEAD = 1,
};

enum Side {
  LEFT = -1,
  STILL = 0,
  RIGHT = 1,
};

class Player {
private:
  class Bullet {
  private:
    Rectangle rec;
    float speed = 340;

    void go(float dt) { rec.y -= speed * dt; }

    void checkForHitExhaustion(Enemy &enemy, size_t &score) {
      if (rec.y < 0)
        exhausted = true;

      if (CheckCollisionRecs(rec, enemy.dest)) {
        exhausted = true;
        enemy.health -= 1;
        score++;
      }
    }

  public:
    bool exhausted = false;

    Bullet(float x, float y, float scale) {
      rec = Rectangle{x - (1 * scale), y, 2 * scale, 4 * scale};
    }

    void update(float dt, std::vector<Enemy> &enemies, size_t &score) {
      go(dt);
      for (Enemy &enemy : enemies)
        checkForHitExhaustion(enemy, score);
    }

    void draw() { DrawRectangleRec(rec, RED); }
  };

  Rectangle src = Rectangle{0, 0, 16, 16};
  Rectangle heart_src = Rectangle{112, 0, 16, 16};
  Rectangle dest;
  int maxSpeed = 280;
  int maxWidth = 0;
  int speed = 0;
  int accelaration = 1500;
  int friction = 1000;
  Side dx = Side::STILL;
  float loadDelay = 0.2;
  float lTime = 0;
  float tTime = 0;
  float tTimeDur = 2;
  size_t tCount = 0;
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

  void control(float dt) {
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

  void handleState(std::vector<Enemy> &enemies) {
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

public:
  size_t lifes = 3;
  size_t score = 0;
  State state = State::IDEAL;

  Player(float x, float y, float scale, int screenWidth) {
    lifes = 3;
    maxWidth = screenWidth;
    dest = Rectangle{x, y, src.width * scale, src.height * scale};
  }

  void update(float dt, float maxWidth, std::vector<Enemy> &enemies) {
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

  void draw(Texture2D &texture) {
    DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, color);
    for (Bullet &bullet : bullets) {
      bullet.draw();
    }
    DrawText(std::to_string(score).c_str(), dest.width / 4, 0, dest.width,
             WHITE);
    for (int i = 1; i <= lifes; i++) {
      DrawTexturePro(
          texture, heart_src,
          Rectangle{maxWidth - (dest.width * i), 0, dest.width, dest.height},
          Vector2{0, 0}, 0, WHITE);
    }
  }
};
