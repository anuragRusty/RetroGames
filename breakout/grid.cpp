#include <Rectangle.hpp>
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;

const Color C1 = {213, 58, 68, 255};
const Color C2 = {92, 196, 128, 255};
const Color C3 = {252, 204, 84, 255};
const Color C4 = {251, 171, 56, 255};
const Color C5 = {246, 87, 152, 255};
const Color C6 = {86, 206, 223, 255};

const vector<Color> colors = {C1, C2, C3, C4, C5, C6};
const Rectangle TileSrc = Rectangle{0, 44, 20, 12};

class Tile {
private:
  Rectangle src;
  Color color;

public:
  Rectangle dest;
  bool exhausted = false;

  Tile(float x, float y, float scale) {
    dest = Rectangle{x, y, TileSrc.width * scale, TileSrc.height * scale};
    color = colors[GetRandomValue(0, colors.size() - 1)];
  }

  void draw(Texture2D &texture) {
    DrawRectangleRec(dest, color);
    DrawRectangleLinesEx(dest, dest.width / 16, BLACK);
  }
};

class Grid {
public:
  vector<Tile> tiles;

  Grid(float screenWidth, int height, float scale) {
    float tileWidth = TileSrc.width * scale;
    float tileHeight = TileSrc.height * scale;
    int rows = floor(screenWidth / tileWidth);

    for (int i = 0; i <= (rows * (height + 1) - 1); i++) {
      int x = (i % rows) * tileWidth;
      int y = (i / rows) * tileHeight;
      Tile tile = Tile(x, y, scale);
      tiles.push_back(tile);
    }
  }

  void update() {
    for (size_t i = 0; i < tiles.size(); i++) {
      if (tiles[i].exhausted) {
        tiles.erase(tiles.begin() + i);
      }
    }
  }

  void draw(Texture2D &texture) {
    for (Tile &tile : tiles)
      tile.draw(texture);
  }
};
