#include "game.hpp"
#include <raylib-cpp.hpp>

int main() {
  Game game = Game();
  raylib::Window window(game.screenWidth, game.screenHeight, "Tetris");
  SetTargetFPS(60);
  while (!window.ShouldClose()) {
    float dt = GetFrameTime();
    game.update(dt);
    BeginDrawing();
    window.ClearBackground(BLACK);
    game.draw();
    EndDrawing();
  }
  return 0;
}
