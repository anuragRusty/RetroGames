#include <cstddef>
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>
using namespace std;

class Anim8 {
  size_t count = 0;
  std::vector<int> frames;
  float time = 0;
  float dur = 0;
  Rectangle src_rec;
  Rectangle dest_rec;

  Anim8(float w, float h, int frame_count, float anim_dur, float src_x,
        float src_y, float dest_x, float dest_y, float scale) {
    src_rec.x = src_x;
    src_rec.y = src_y;
    src_rec.width = w;
    src_rec.height = h;
    dest_rec.x = dest_x;
    dest_rec.y = dest_y;
    dest_rec.width = w * scale;
    dest_rec.height = h * scale;
    dur = anim_dur;
    for (int i = 0; i < frame_count; i++) {
      frames.push_back(i * src_rec.width);
    }
  }

  void update(float dt) {
    if (time > dur) {
      count %= frames.size();
      src_rec.x = frames[count];
      time = 0;
    }
    time += dt;
  }

  void draw(Texture2D &sheet) {
    DrawTexturePro(sheet, src_rec, dest_rec, Vector2{0, 0}, 0, WHITE);
  }
};
