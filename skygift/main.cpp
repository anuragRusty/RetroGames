#include "background.cpp"
#include "gift.cpp"
#include "plane.cpp"
#include "raylib-cpp.hpp"
#include <raylib.h>

int main() {
  float screenWidth = 800;
  float screenHeight = 800;

  raylib::Window window(screenWidth, screenHeight, "SkyGift");
  raylib::Texture texture("assets/sheet.png");

  Background bg = Background(screenWidth, screenHeight);

  Gift gt = Gift(screenHeight / 6, screenHeight / 6, screenHeight / 16);

  Plane plane = Plane(screenHeight / 6, 240);

  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(RAYWHITE);
    float dt = GetFrameTime();
    // DRAW OBJS
    bg.draw(texture);
    gt.draw(texture);
    plane.draw(texture);
    // UPDATE OBJS
    gt.update(dt, screenHeight);
    plane.update(dt, screenWidth);
    EndDrawing();
  }

  // UnloadTexture() and CloseWindow() are called automatically.

  return 0;
}
