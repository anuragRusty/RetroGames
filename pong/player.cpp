#include "player.hpp"
#include "ball.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
using namespace std;

Player::Player(PlayerType p, float spd, float size, float maxWidth, float maxHeight) {
  speed = spd;
  rec.width = size;
  rec.height = size * 3;
  rec.x = (p == 0 ? 0 : 1) * (maxWidth - rec.width);
  rec.y = maxHeight / 2 - rec.height;
  PlayerType player = p;
  color = colors[p];
}

void Player::update(float dt, int maxWidth, int maxHeight, Ball &ball) {
  go(dt, maxWidth, maxHeight);
  control(ball, maxHeight);
}

void Player::control(Ball &ball, int maxHeight) {
  switch (player) {
   case Player1:
    if (IsKeyPressed(KEY_UP) && rec.y > 0) {
      dir = Dir::UP;
      std::cout << "KEY PRESSED UP" << endl;
    } else if (IsKeyPressed(KEY_DOWN) && rec.y < (maxHeight - rec.height)) {
      dir = Dir::DOWN;
    } else {
      dir = Dir::STILL;
    }
   break;
   case Player2:
    if (IsKeyPressed(KEY_W) && rec.y > 0) {
      dir = Dir::UP;
    } else if (IsKeyPressed(KEY_S) && rec.y < (maxHeight - rec.height)) {
      dir = Dir::DOWN;
    } else {
      dir = Dir::STILL;
    }
   break;
   case Computer:
    float mid_y = rec.y + rec.height / 2;
    if (ball.vec.y < mid_y && rec.y > 0) {
      dir = Dir::UP;
    } else if (ball.vec.y > mid_y && rec.y < (maxHeight - rec.height)) {
      dir = Dir::DOWN;
    } else {
      dir = Dir::STILL;
    }
    break;
    }
  }

void Player::go(float dt, int maxWidth, int maxHeight) { 
  rec.y += dir * speed * dt; 
}

void Player::draw() { 
  DrawRectangleRec(rec, color);
}
