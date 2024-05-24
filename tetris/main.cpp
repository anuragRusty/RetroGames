#include "game.hpp"
#include <raylib-cpp.hpp>

int main() {
  int screenWidth = 400;
  int screenHeight = 800;
  Game game = Game();

  raylib::Window window(screenWidth, screenHeight, "Tetris");

  SetTargetFPS(60);
  while (!window.ShouldClose()) {
    float dt = GetFrameTime();
    game.update(dt);
    BeginDrawing();
    window.ClearBackground(RAYWHITE);
    game.draw();
    EndDrawing();
  }
  return 0;
}
