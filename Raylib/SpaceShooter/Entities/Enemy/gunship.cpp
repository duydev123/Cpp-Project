#include "gunship.h"
#include <raymath.h>

GunShip::GunShip() {}
GunShip::GunShip(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
}
GunShip::~GunShip() {}

Vector2 GunShip::CalculateDirection(Vector2 targetPos) {
  Vector2 dir = Vector2Subtract(targetPos, this->position);
  return Vector2Normalize(dir);
}

bool GunShip::CanShoot()
{
  if (this->shootTimer >= this->shootCooldown)
  {
    return true;
  }
  return false;
}

void GunShip::ResetShootTimer()
{
  this->shootTimer = 0.0f;
}

Vector2 GunShip::TargetSlot() {
  return this->targetSlot;
}
void GunShip::TargetSlot(Vector2 target) {
  this->targetSlot = target;
}
Vector2 GunShip::Position() {
  return this->position;
}
void GunShip::Draw() {
  DrawRectangleV(this->position, this->size, RED);
}

void GunShip::Update(float frametime) {
  this->shootTimer += frametime;
  this->position = Vector2MoveTowards(this->position, {120 * this->targetSlot.x + 90, 120 * this->targetSlot.y + 60}, this->speed);
}

Bullet GunShip::Shoot(Vector2 targetDirection) {
  return Bullet({this->position.x + this->size.x / 2, this->position.y + this->size.y / 2}, targetDirection,  8);
}

