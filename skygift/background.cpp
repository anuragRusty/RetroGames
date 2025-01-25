#include "background.hpp"

Background::Background(float w, float h) {
  screenWidth = w;
  screenHeight = h;
  shadeHeight = h / 6;
  giftDestRec = Rectangle{0, 0, shadeHeight / 2, shadeHeight / 2};
  skyShade = Rectangle{0, 0, w, h};
  skyShade1 = Rectangle{0, shadeHeight, w, shadeHeight};
  skyShade2 = Rectangle{0, shadeHeight * 2, w, shadeHeight};
  skyShade3 = Rectangle{0, shadeHeight * 3, w, shadeHeight};
  skyShade4 = Rectangle{0, shadeHeight * 4, w, shadeHeight};

  size_t grassTiles = screenWidth / shadeHeight;
  for (size_t i = 0; i < grassTiles; i++) {
      Rectangle grassDestRec =
          Rectangle{i * shadeHeight, shadeHeight * 5, shadeHeight, shadeHeight};
      grassDestRecs.push_back(grassDestRec);
  }
  size_t cloudCount = GetRandomValue(2, 4);
  for (size_t i = 0; i < cloudCount; i++) {
      float randomX = GetRandomValue(shadeHeight, (w - shadeHeight));
      Rectangle cloudDestRec = Rectangle{randomX, (i * shadeHeight / 2),shadeHeight / 2, shadeHeight / 2};
      cloudDestRecs.push_back(cloudDestRec);
  }
  for (size_t i = 0; i < 3; i++) {
      Rectangle heartDestRec = Rectangle{i * shadeHeight / 2, h - shadeHeight / 2, shadeHeight / 2,shadeHeight / 2};
      heartDestRecs.push_back(heartDestRec);
    }
  }

void Background::update(int s, int l) {
  score = s;
  life = l;
}

void Background::draw(Texture2D &texture) {
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
  DrawText(text.c_str(), shadeHeight / 2, shadeHeight / 10, shadeHeight / 2,BLACK);
}
