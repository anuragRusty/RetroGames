#ifndef ANIM8_H
#define ANIM8_H

#include <iostream>
#include <raylib-cpp.hpp>
#include <vector>

using namespace std;

class Anim8 {
private:
  std::vector<int> frames;
  float time = 0;
  float dur = 0;
  Rectangle src_rec;

public:
  size_t count = 0;
  Rectangle dest_rec;

  void init(float w, float h, int frame_count, float anim_dur, float src_x,float src_y, float dest_x, float dest_y, float scale);
  void update(float dt);
  void draw(Texture2D &sheet);
};

#endif