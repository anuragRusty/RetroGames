#include "game.hpp"
#include "raylib-cpp.hpp"

int main() {
  int screenWidth = TILE_SIZE * 16;
  int screenHeight = screenWidth;
  Game game = Game();
  raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");
  const raylib::Texture texture("assets/sheet.png");
  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(BLACK);
    float dt = GetFrameTime();
    // UPDATE OBJS
    game.update(dt);
    // DRAW OBJS
    game.draw(texture);
    EndDrawing();
  }
  return 0;
}
