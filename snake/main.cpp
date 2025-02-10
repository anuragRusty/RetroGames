#include "game.hpp"
#include "raylib-cpp.hpp"

int main() {
  const int TILE_SIZE = 48;
  int screenWidth = 48 * 16;
  int screenHeight = screenWidth;
  Game game = Game();
  raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(BLACK);
    float dt = GetFrameTime();
    // UPDATE OBJS
    game.update(dt);
    // DRAW OBJS
    game.draw();
    EndDrawing();
  }
  return 0;
}
