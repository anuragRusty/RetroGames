#include <functional>
#include <future>
#include <iostream>
#include <raylib.h>

using namespace std;

class Button {
private:
  Rectangle rec;
  string text;
  bool hover = false;
  Color color;
public:
  Button(float x, float y, float textSize, string name,Color clr) {
    rec.x = x;
    rec.y = y;
    rec.height = textSize;
    rec.width = textSize * (name.size() / 1.3);
    text = name;
    color = clr;
  }

  void onClick(function<void()> func) {
    Vector2 vec = GetMousePosition();
    if (CheckCollisionPointRec(vec, rec)) {
      hover = true;
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        func();
      }
    } else {
      hover = false;
    }
  }

  void draw() {
    DrawText(text.c_str(), rec.x + (rec.height / 8), rec.y, rec.height, color);
    if (hover)
      DrawRectangleLinesEx(rec, 2, color);
  }
};
