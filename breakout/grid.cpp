#include <Rectangle.hpp>
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;

const int TYPES_TILES = 6;
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
  }

  void draw(Texture2D &texture) {
    if (!exhausted)
      DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, WHITE);
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

  void draw(Texture2D &texture) {
    for (Tile &tile : tiles)
      tile.draw(texture);
  }
};
