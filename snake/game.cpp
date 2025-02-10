#include "game.hpp"

void Game::update(float dt) {
  function<void()> game_func = [&]() { state = GameState::RUNNING; };
  function<void()> restart_func = [&]() {
    snake = Snake(TILE_SIZE, TILE_SIZE, TILE_SIZE);
    game_func();
  };
  function<void()> pause_game = [&]() { state = GameState::PAUSED; };
  function<void()> exit_func = [&]() { CloseWindow(); };
  function<void()> check_game_over = [&]() {
    if (snake.biten) {
      state = GameState::GAMEOVER;
    }
  };
  switch (state) {
  case MENU:
    start.onClick(game_func);
    exit.onClick(exit_func);
    break;
  case RUNNING:
    food.update(SCREEN_WIDTH, SCREEN_HEIGHT);
    snake.update(dt, food, SCREEN_WIDTH, SCREEN_HEIGHT);
    paused.onClick(pause_game);
    check_game_over();
    break;
  case PAUSED:
    resume.onClick(game_func);
    break;
  case GAMEOVER:
    restart.onClick(restart_func);
    break;
  }
}

void Game::score() {
  string score = "SCORE " + to_string((snake.segments.size() - 2));
  raylib::DrawText(score, TILE_SIZE / 4, TILE_SIZE / 4, TILE_SIZE, WHITE);
}

void Game::drawState(string text) {
  auto x = SCREEN_WIDTH / 2 - (text.size() / 2.5) * TILE_SIZE;
  auto y = SCREEN_HEIGHT / 3;
  raylib::DrawText(text.c_str(), x, y, TILE_SIZE, WHITE);
}

void Game::draw() {
  switch (state) {
  case MENU:
    start.draw();
    exit.draw();
    break;
  case RUNNING:
    snake.draw();
    food.draw();
    score();
    paused.draw();
    break;
  case GAMEOVER:
    drawState("GAME OVER");
    score();
    restart.draw();
    break;
  case PAUSED:
    snake.draw();
    food.draw();
    score();
    drawState("GAME PAUSED");
    resume.draw();
    break;
  }
}