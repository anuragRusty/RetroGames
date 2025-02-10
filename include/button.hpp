#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

class Button {
private:
  Rectangle rec;
  string text;
  bool hover = false;
  Color color;
public:
  Button(float x, float y, float textSize, string name,Color clr);
  void onClick(function<void()> func);
  void draw();
};

#endif