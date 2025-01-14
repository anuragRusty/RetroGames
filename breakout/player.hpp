#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <cstddef>
#include <raylib-cpp.hpp>

const Rectangle playerSrc = Rectangle{0, 32, 32, 12};

enum HorizontalSide {
  LEFT = -1,
  STILL = 0,
  RIGHT = 1,
};

class Player {
private:
  float speed = 0;
  float maxWidth = 0;
  HorizontalSide dx;
  
  void go(float dt);

public:
  int life = 3;
  int score = 0;
  Rectangle dest;
  Rectangle leftDest;
  Rectangle midDest;
  Rectangle rightDest;

  Player(float screenWidth, float screenHeight, float scale, float spd);
  void update(float dt);
  void draw(Texture2D &texture);
};

#endif