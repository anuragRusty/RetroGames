#include "food.cpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>

using namespace std;

enum DIR {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

class Snake {
public:
  DIR dir = DIR::RIGHT;
  bool biten = false;
  float upTime = 0;
  std::vector<Rectangle> segments;

  Snake(float x, float y, float size) {
    Rectangle rec = Rectangle{x, y, size, size};
    segments.push_back(rec);
    segments.push_back(rec);
  }

  void update(float dt, Food &food, int maxWidth, int maxHeight) {
    go(maxWidth, maxHeight);
    control();
    eat(food);
    resetGame();
    upTime += dt;
  }

  void eat(Food &food) {
    Rectangle head = segments[0];
    if (food.rec.x == head.x && food.rec.y == head.y) {
      food.eaten = true;
      expand();
    }
  }

  void expand() {
    Rectangle tail = segments[segments.size() - 1];
    switch (dir) {
    case UP:
      tail.y += tail.width;
      break;
    case DOWN:
      tail.y -= tail.width;
      break;
    case LEFT:
      tail.x += tail.width;
      break;
    case RIGHT:
      tail.x -= tail.width;
      break;
    }
    segments.push_back(tail);
  }

  void updateSegments() {
    for (size_t i = segments.size() - 1; i > 0; i--) {
      segments[i].x = segments[i - 1].x;
      segments[i].y = segments[i - 1].y;
    }
  }

  void go(int maxWidth, int maxHeight) {
    Rectangle &head = segments[0];
    if (head.x > maxWidth) {
      head.x = 0;
    } else if (head.y > maxHeight) {
      head.y = 0;
    } else if (head.x < 0) {
      head.x = maxWidth;
    } else if (head.y < 0) {
      head.y = maxHeight;
    }

    if (upTime > 0.20) {
      switch (dir) {
      case UP:
        head.y -= head.width;
        break;
      case DOWN:
        head.y += head.width;
        break;
      case LEFT:
        head.x -= head.width;
        break;
      case RIGHT:
        head.x += head.width;
        break;
      }
      updateSegments();
      upTime = 0;
    }
  }

  void control() {
    if (IsKeyDown(KEY_DOWN)) {
      dir = DIR::DOWN;
    } else if (IsKeyDown(KEY_UP)) {
      dir = DIR::UP;
    } else if (IsKeyDown(KEY_LEFT)) {
      dir = DIR::LEFT;
    } else if (IsKeyDown(KEY_RIGHT)) {
      dir = DIR::RIGHT;
    }
  }

  void resetGame() {
    Rectangle head = segments[0];

    for (size_t i = 2; i < segments.size(); i++) {
      if (head.x == segments[i].x && head.y == segments[i].y) {
        biten = true;
      }
    }
  }

  void draw() {
    for (const auto segment : segments) {
      DrawRectangleRec(segment, GREEN);
      DrawRectangleLinesEx(segment, segment.width / 16, BLACK);
    }
  }
};
