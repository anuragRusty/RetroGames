#include <cmath>
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
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
public:
  float screenWidth;
  float screenHeight;
  float shadeHeight;
  int score = 0;
  int life = 3;
  Rectangle skyShade;
  Rectangle skyShade1;
  Rectangle skyShade2;
  Rectangle skyShade3;
  Rectangle skyShade4;
  Rectangle giftDestRec;
  vector<Rectangle> heartDestRecs;
  vector<Rectangle> cloudDestRecs;
  vector<Rectangle> grassDestRecs;

  Background(float w, float h) {
    screenWidth = w;
    screenHeight = h;
    shadeHeight = h / 6;
    giftDestRec = Rectangle{0, 0, shadeHeight / 2, shadeHeight / 2};
    skyShade = Rectangle{0, 0, w, h};
    skyShade1 = Rectangle{0, shadeHeight, w, shadeHeight};
    skyShade2 = Rectangle{0, shadeHeight * 2, w, shadeHeight};
    skyShade3 = Rectangle{0, shadeHeight * 3, w, shadeHeight};
    skyShade4 = Rectangle{0, shadeHeight * 4, w, shadeHeight};

    int grassTiles = screenWidth / shadeHeight;
    for (int i = 0; i < grassTiles; i++) {
      Rectangle grassDestRec =
          Rectangle{i * shadeHeight, shadeHeight * 5, shadeHeight, shadeHeight};
      grassDestRecs.push_back(grassDestRec);
    }

    int cloudCount = GetRandomValue(2, 4);
    for (int i = 0; i < cloudCount; i++) {
      float randomX = GetRandomValue(shadeHeight, (w - shadeHeight));
      Rectangle cloudDestRec = Rectangle{randomX, (i * shadeHeight / 2),
                                         shadeHeight / 2, shadeHeight / 2};
      cloudDestRecs.push_back(cloudDestRec);
    }

    for (int i = 0; i < 3; i++) {
      Rectangle heartDestRec =
          Rectangle{i * shadeHeight / 2, h - shadeHeight / 2, shadeHeight / 2,
                    shadeHeight / 2};
      heartDestRecs.push_back(heartDestRec);
    }
  }

  void update(int s, int l) {
    score = s;
    life = l;
  }

  void draw(Texture2D &texture) {
    DrawRectangleRec(skyShade, SKYSHADE);
    DrawRectangleRec(skyShade1, SKYSHADE1);
    DrawRectangleRec(skyShade2, SKYSHADE2);
    DrawRectangleRec(skyShade3, SKYSHADE3);
    DrawRectangleRec(skyShade4, SKYSHADE4);

    for (const auto grassDestRec : grassDestRecs) {
      DrawTexturePro(texture, grassSrc, grassDestRec, Vector2{0, 0}, 0, WHITE);
    }

    for (const auto cloudDestRec : cloudDestRecs) {
      DrawTexturePro(texture, cloudSrc, cloudDestRec, Vector2{0, 0}, 0, WHITE);
    }

    for (size_t i = 0; i < life; i++) {
      Rectangle heartDestRec = heartDestRecs[i];
      DrawTexturePro(texture, heartSrc, heartDestRec, Vector2{0, 0}, 0, WHITE);
    }

    DrawTexturePro(texture, giftSrc, giftDestRec, Vector2{0, 0}, 0, WHITE);
    string text = "x" + to_string(score);
    DrawText(text.c_str(), shadeHeight / 2, shadeHeight / 10, shadeHeight / 2,
             BLACK);
  }
};
