#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <cmath>
#include <iostream>
#include <raylib-cpp.hpp>
#include <string>
#include <vector>

using namespace std;

const Color SKYSHADE = Color{13, 151, 255, 255};
const Color SKYSHADE1 = Color{62, 172, 255, 255};
const Color SKYSHADE2 = Color{96, 186, 253, 255};
const Color SKYSHADE3 = Color{120, 196, 253, 255};
const Color SKYSHADE4 = Color{147, 209, 255, 255};

const Rectangle cloudSrc = Rectangle{0, 96, 32, 32};
const Rectangle grassSrc = Rectangle{0, 0, 32, 32};
const Rectangle giftSrc = Rectangle{0, 64, 32, 32};
const Rectangle heartSrc = Rectangle{0, 128, 32, 32};

class Background {
private:
  float screenWidth;
  float screenHeight;
  float shadeHeight;
  size_t score = 0;
  size_t life = 3;
  Rectangle skyShade;
  Rectangle skyShade1;
  Rectangle skyShade2;
  Rectangle skyShade3;
  Rectangle skyShade4;
  Rectangle giftDestRec;
  vector<Rectangle> heartDestRecs;
  vector<Rectangle> cloudDestRecs;
  vector<Rectangle> grassDestRecs;

public:
  Background(float w, float h);
  void update(int s, int l);
  void draw(Texture2D &texture);
};

#endif
