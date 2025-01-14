#include "ball.hpp"
#include "player.hpp"
#include <iostream>
#include <raylib-cpp.hpp>

using namespace std;

void Ball::go(float dt) {
  dest.x += speed * dt * dx;
  dest.y += speed * dt * dy;
}

void Ball::hitAndBounce(Grid &grid) {
  for (Tile &tile : grid.tiles) {
     if (CheckCollisionCircleRec(Vector2{dest.x, dest.y}, dest.width / 2,tile.dest) && !tile.exhausted) {
        tile.exhausted = true;
        switch (dx) {
        case HorizontalSide::LEFT:
          dx = HorizontalSide::RIGHT;
          break;
        case HorizontalSide::STILL:
          break;
        case HorizontalSide::RIGHT:
          dx = HorizontalSide::LEFT;
          break;
        }
        switch (dy) {
        case VerticalSide::TOP:
          dy = VerticalSide::DOWN;
          break;
        case VerticalSide::DOWN:
          dy = VerticalSide::TOP;
          break;
        }
      };
    }
  }

void Ball::bounce(Player &player) {
  if (dest.x >= maxWidth) {
      dx = HorizontalSide::LEFT;
   }
  if (dest.y >= maxHeight) {
      dy = VerticalSide::TOP;
      player.life--;
  }
  if (dest.x <= dest.width / 2) {
      dx = HorizontalSide::RIGHT;
  }
  if (dest.y <= dest.height / 2) {
      dy = VerticalSide::DOWN;
  }

  bool leftCollison = CheckCollisionCircleRec(Vector2{dest.x, dest.y}, dest.width / 2, player.leftDest);
  bool midCollison = CheckCollisionCircleRec(Vector2{dest.x, dest.y},dest.width / 2, player.midDest);
  bool rightCollison = CheckCollisionCircleRec(Vector2{dest.x, dest.y}, dest.width / 2, player.rightDest);
  bool fullCollison = CheckCollisionCircleRec(Vector2{dest.x, dest.y},dest.width / 2, player.dest);

  if (leftCollison) {
    dx = HorizontalSide::LEFT;
   }

  if (rightCollison) {
    dx = HorizontalSide::RIGHT;
  }

  if (midCollison) {
    dx = HorizontalSide::STILL;
  }

  if (fullCollison) {
      dy = VerticalSide::TOP;
  }
}

Ball::Ball(float screenWidth, float screenHeight, float scale, float spd) {
  dest = Rectangle{screenWidth / 2, screenHeight / 2, BallSrc.width * scale, BallSrc.height * scale};
  vec = Vector2{dest.width / 2, dest.height / 2};
  maxWidth = screenWidth - dest.width / 2;
  maxHeight = screenHeight - dest.height / 2;
  speed = spd;
}

void Ball::update(float dt, Player &player, Grid &grid) {
  go(dt);
  bounce(player);
  hitAndBounce(grid);
}

void Ball::draw(Texture2D &texture) {
  DrawTexturePro(texture, BallSrc, dest, vec, 0, WHITE);
}
