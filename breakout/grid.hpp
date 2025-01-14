#ifndef GRID_H
#define GRID_H

#include <cmath>
#include <iostream>
#include <raylib-cpp.hpp>
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

  Tile(float x, float y, float scale);
  void draw(Texture2D &texture);
};

class Grid {
public:
  vector<Tile> tiles;

  Grid(float screenWidth, int height, float scale);
  void update();
  void draw(Texture2D &texture);
};

#endif