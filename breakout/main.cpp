#include "game.hpp"
#include "raylib-cpp.hpp"

int main() {
  Game game = Game();
  raylib::Window window(game.screenWidth, game.screenHeight, game.title);
  raylib::Texture texture("assets/sheet.png");
  SetTargetFPS(60);
  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(BLACK);
    float dt = GetFrameTime();
    game.update(dt);
    game.draw(texture);
    EndDrawing();
  }

  return 0;
}
