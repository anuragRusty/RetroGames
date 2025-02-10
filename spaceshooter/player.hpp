#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.hpp"
#include "enemy.hpp"
#include <raylib-cpp.hpp>
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

  void applyAccelration(float dt);
  void applyFriction(float dt);
  void go(float dt);
  void shoot(float dt);
  void tinting(float dt);
  void control(float dt);
  void handleState(std::vector<Enemy> &enemies);

public:
  size_t lifes = 3;
  size_t score = 0;
  State state = State::IDEAL;

  Player(float x, float y, float scale, int screenWidth);
  void update(float dt, float maxWidth, std::vector<Enemy> &enemies);
  void draw(Texture2D &texture);
};

#endif