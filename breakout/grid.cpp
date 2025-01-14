#include "grid.hpp"
#include <cmath>
#include <iostream>
#include <raylib-cpp.hpp>
#include <vector>

using namespace std;

Tile::Tile(float x, float y, float scale) {
  dest = Rectangle{x, y, TileSrc.width * scale, TileSrc.height * scale};
  color = colors[GetRandomValue(0, colors.size() - 1)];
}

void Tile::draw(Texture2D &texture) {
  DrawRectangleRec(dest, color);
  DrawRectangleLinesEx(dest, dest.width / 16, BLACK);
}

Grid::Grid(float screenWidth, int height, float scale) {
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

void Grid::update() {
  for (size_t i = 0; i < tiles.size(); i++) {
    if (tiles[i].exhausted) {
        tiles.erase(tiles.begin() + i);
    }
  }
}

void Grid::draw(Texture2D &texture) {
  for (Tile &tile : tiles)
    tile.draw(texture);
}
