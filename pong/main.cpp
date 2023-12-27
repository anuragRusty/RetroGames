#include "game.cpp"
#include <iostream>
#include <raylib-cpp.hpp>

int main() {
  Game game = Game();
  raylib::Window window(game.screenWidth, game.screenHeight, "Pong");
  SetTargetFPS(60);
  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(BLACK);
    float dt = GetFrameTime();
    // UPDATE OBJS
    game.update(dt);
    // DRAW OBJS
    EndDrawing();
    game.draw();
  }
  return 0;
}
