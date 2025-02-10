#include <cmath>
#include <cstdlib>
#include <raylib-cpp.hpp>
#include <raymath.h>

class Food {
public:
  bool eaten = false;
  Rectangle rec;

  Food(float size) {
    rec.x = 48 * 7;
    rec.y = 48 * 2;
    rec.width = size;
    rec.height = size;
  }

  void update(int maxWidth, int maxHeight) {
    int rows = std::floor(maxWidth / rec.width);
    int cols = std::floor(maxHeight / rec.width);
    if (eaten) {
      rec.x = GetRandomValue(1, rows - 1) * rec.width;
      rec.y = GetRandomValue(1, cols - 1) * rec.width;
      eaten = false;
    }
  }

  void draw() {
    DrawRectangleRec(rec, RED);
    DrawRectangleLinesEx(rec, rec.width / 16, BLACK);
  }
};
