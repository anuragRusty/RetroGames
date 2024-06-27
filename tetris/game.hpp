#ifndef GAME_H
#define GAME_H

#include "../libs/button.cpp"
#include "grid.hpp"
#include "shape.hpp"

const Color BTN_COLOR = WHITE;

enum GameState {
  MENU,
  RUNNING,
  PAUSED,
  GAMEOVER,
};

class Game {
public:
  size_t screenWidth = 650;
  size_t uiMargin = 250;
  size_t screenHeight = 800;

  void update(float dt);
  void draw();

private:
  Grid grid = Grid();
  Shape currShape = Shape();
  Shape nextShape = Shape();
  size_t score = 0;
  size_t btnX = screenWidth / 3;
  size_t btnY = screenHeight / 3;
  size_t fontSize = screenHeight / 16;
  GameState state = MENU;
  Button start = Button(btnX, btnY, fontSize, "START", BTN_COLOR);
  Button exit = Button(btnX, btnY + fontSize, fontSize, "EXIT", BTN_COLOR);
  Button paused = Button(screenWidth - (3.5 * 1.3 * (fontSize)),
                         screenHeight - fontSize, fontSize, "PAUSE", BTN_COLOR);
  Button restart =
      Button(screenWidth - (4.5 * 1.3 * fontSize), screenHeight - fontSize,
             fontSize, "RESTART", BTN_COLOR);
  Button resume =
      Button(screenWidth - (5.5 * 1.3 * fontSize), screenHeight - fontSize,
             fontSize, "RESUME", BTN_COLOR);

  void handleShape();
  void handleState(Grid const &grid);
  void resetGame();
  void drawScore();
  void drawNextShape();
  void drawState(string str);
};

#endif // !DEBUG
