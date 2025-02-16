#include "snake.hpp"
#include "game.hpp"

const Rectangle HeadSrcRec = {32,0,16,16};
const Rectangle BodySrcRec = {16,0,16,16};

Snake::Snake(float x, float y, float size) {
    Rectangle rec = Rectangle{x, y, size, size};
    segments.push_back(rec);
}

void Snake::update(float dt, Food &food, int maxWidth, int maxHeight) {
    go(maxWidth, maxHeight);
    control();
    eat(food);
    resetGame();
    upTime += dt;
}

void Snake::eat(Food &food) {
  const Rectangle &head = segments[0];
  if (CheckCollisionCircles({head.x,head.y},TILE_SIZE/2,{food.rec.x,food.rec.y},TILE_SIZE/2)) {
    food.eaten = true;
    expand();
  }
}

void Snake::expand() {
  Rectangle tail = segments[segments.size() - 1];
  switch (dir) {
  case UP:
    tail.y += tail.width;
    break;
  case DOWN:
    tail.y -= tail.width;
    break;
  case LEFT:
    tail.x += tail.width;
    break;
  case RIGHT:
    tail.x -= tail.width;
    break;
  }
  segments.push_back(tail);
}

void Snake::updateSegments() {
  for (size_t i = segments.size() - 1; i > 0; i--) {
    segments[i].x = segments[i - 1].x;
    segments[i].y = segments[i - 1].y;
  }
}

void Snake::go(int maxWidth, int maxHeight) {
  Rectangle &head = segments[0];
  if (head.x > (maxWidth - TILE_SIZE/2)) {
    head.x = TILE_SIZE/2;
  } else if (head.y > (maxHeight - TILE_SIZE/2)) {
      head.y = TILE_SIZE/2;
  } else if (head.x < TILE_SIZE/2) {
      head.x = maxWidth - TILE_SIZE/2;
  } else if (head.y < TILE_SIZE/2) {
      head.y = maxHeight - TILE_SIZE/2;
  }
  if (upTime > 0.20) {
    switch (dir) {
      case UP:
        head.y -= head.width;
        break;
      case DOWN:
        head.y += head.width;
        break;
      case LEFT:
        head.x -= head.width;
        break;
      case RIGHT:
        head.x += head.width;
        break;
      }
    updateSegments();
    upTime = 0;
  }
}

void Snake::control() {
  if (IsKeyDown(KEY_DOWN) && dir != DIR::UP) {
    dir = DIR::DOWN;
  } else if (IsKeyDown(KEY_UP) && dir != DIR::DOWN) {
    dir = DIR::UP;
  } else if (IsKeyDown(KEY_LEFT) && dir != DIR::RIGHT) {
    dir = DIR::LEFT;
  } else if (IsKeyDown(KEY_RIGHT) && dir != DIR::LEFT) {
    dir = DIR::RIGHT;
  }
}

void Snake::resetGame() {
  Rectangle head = segments[0];
  for (size_t i = 2; i < segments.size(); i++) {
    if (head.x == segments[i].x && head.y == segments[i].y) {
      biten = true;
    }
  }
}

void Snake::draw(const Texture2D &texture) {
  const Rectangle &head = segments[0];
  DrawTexturePro(texture,HeadSrcRec,head,Vector2{TILE_SIZE/2,TILE_SIZE/2},dir,WHITE);
  for (size_t i = 1; i < segments.size(); i++) {
    const Rectangle &segment = segments[i];
    if(i <= 1){
      DrawTexturePro(texture,HeadSrcRec,segment,Vector2{TILE_SIZE/2,TILE_SIZE/2},dir,WHITE);
    }else{
     DrawTexturePro(texture,BodySrcRec,segment,Vector2{TILE_SIZE/2,TILE_SIZE/2},dir,WHITE);
    }
  }
}
