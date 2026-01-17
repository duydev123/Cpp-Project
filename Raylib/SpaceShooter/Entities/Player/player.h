#pragma once
#include <raylib.h>
#include "../Bullet/bullet.h"
#include <vector>
class Player {
  private:
    Vector2 position;
    Vector2 size;
    float speed = 8.0f;
    float shootTimer = 0.0f;
    float shootCooldown = 0.2f;

  public:
    Player();
    Player(Vector2 position, Vector2 size);
    ~Player();

    bool CanShoot();
    void ResetShootTimer();

    Vector2 Position();

    void Update(float frametime);
    void Draw();

    Bullet Shoot();
};