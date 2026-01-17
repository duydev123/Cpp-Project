#include "bullet.h"
#include <raymath.h>
Bullet::Bullet() {
  this->direction = {0, -1};
}
Bullet::Bullet(Vector2 position, float radius) {
  this->position = position;
  this->radius = radius;
  this->direction = {0, -1};
}
Bullet::Bullet(Vector2 position, Vector2 direction,  float radius)
{
  this->position = position;
  this->radius = radius;
  this->direction = direction;
}
Bullet::~Bullet() {}

Vector2 Bullet::Position() {
  return this->position;
}
bool Bullet::IsOutOfScreen() {
  if(this->position.y > GetScreenHeight() ) {
    return true;
  }
  return false;
}
void Bullet::Draw() {
  DrawCircleV(this->position, this->radius, RED);
}

void Bullet::Update() {
  this->position = Vector2Add(this->position, Vector2Scale(direction, speed));
}