#pragma once
#include <raylib.h>
#include "../Bullet/bullet.h"

class GunShip {
  private:
    Vector2 position;
    Vector2 size;
    Vector2 targetSlot;
    float speed = 8.0f;
    float shootTimer = 0.0f;
    float shootCooldown = 2.0f;

  public:
    GunShip();
    GunShip(Vector2 position, Vector2 size);
    ~GunShip();

    Vector2 CalculateDirection(Vector2 targetPos);
    bool CanShoot();
    void ResetShootTimer();
    Vector2 TargetSlot();
    void TargetSlot(Vector2 target);
    Vector2 Position();


    void Update(float frametime);
    void Draw();

    Bullet Shoot(Vector2 targetDirection);
};