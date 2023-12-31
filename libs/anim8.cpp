#include <cstddef>
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>
using namespace std;

class Anim8 {
private:
  std::vector<int> frames;
  float time = 0;
  float dur = 0;
  Rectangle src_rec;
  Rectangle dest_rec;

public:
  size_t count = 0;

  void init(float w, float h, int frame_count, float anim_dur, float src_x,
            float src_y, float dest_x, float dest_y, float scale) {
    src_rec = Rectangle{src_x, src_y, w, h};
    dest_rec = Rectangle{dest_rec.x, dest_rec.y, w * scale, h * scale};
    dur = anim_dur;
    for (int i = 0; i < frame_count; i++) {
      frames.push_back(i * src_rec.width);
    }
  }

  void update(float dt) {
    if (time > dur) {
      count++;
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
