#include "game.hpp"
#include "raylib-cpp.hpp"

int main() {
  Game game = Game();
  raylib::Window window(game.screenWidth, game.screenHeight, "SpaceShooter");
  raylib::Texture texture("assets/sheet.png");
  SetTargetFPS(60);
  while (!window.ShouldClose()) {
    BeginDrawing();
    window.ClearBackground(RAYWHITE);
    float dt = GetFrameTime();
    game.update(dt);
    game.draw(texture);
    EndDrawing();
  }
  return 0;
}
