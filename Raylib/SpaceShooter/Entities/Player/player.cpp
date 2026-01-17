#include "player.h"
#include <raymath.h>
#include "../Bullet/bullet.h"

Player::Player() {}
Player::Player(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
}
Player::~Player() {}

bool Player::CanShoot() {
  if(this->shootTimer >= this->shootCooldown) {
    return true;
  }
  return false;
}

void Player::ResetShootTimer() {
  this->shootTimer = 0.0f;
}

Vector2 Player::Position() {
  return this->position;
}

void Player::Draw() {
  DrawRectangleV(this->position, this->size, GREEN);
}

Bullet Player::Shoot() {
  Bullet bullet = {{this->position.x + this->size.x / 2, this->position.y - this->size.y / 2}, 8};
  return bullet;
}


void Player::Update(float frametime) {
  this->shootTimer += frametime;
  Vector2 direction = {0, 0};

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    direction.x -= 1;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    direction.x += 1;
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    direction.y -= 1;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    direction.y += 1;

  if (direction.x != 0 || direction.y != 0)
  {
    Vector2 movement = Vector2Scale(direction, this->speed );
    this->position = Vector2Add(this->position, movement);
  }
}