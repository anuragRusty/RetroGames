#include "game.hpp"
#include "player.hpp"
#include <iostream>
#include <raylib-cpp.hpp>

Game::Game() {}

void Game::update(float dt) {
 switch (state) {
   case MENU:
     break;
   case RUNNING:
     player1.update(dt, screenWidth, screenHeight, ball);
     player2.update(dt, screenWidth, screenHeight, ball);
     ball.update(dt, player1.rec, player2.rec, maxWidth, maxHeight);
     break;
   case RUNNING2:
     player1.update(dt, screenWidth, screenHeight, ball);
     computer.update(dt, screenWidth, screenHeight, ball);
     ball.update(dt, player1.rec, computer.rec, maxWidth, maxHeight);
     break;
   case PAUSED:
    break;
  }
}

void Game::draw() {
  switch (state) {
   case MENU:
    break;
   case RUNNING:
    player1.draw();
    player2.draw();
    ball.draw();
    break;
   case RUNNING2:
    player1.draw();
    computer.draw();
    ball.draw();
    break;
  case PAUSED:
      break;
  }
}
