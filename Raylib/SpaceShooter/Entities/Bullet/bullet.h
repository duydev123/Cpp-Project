#pragma once
#include <raylib.h>

class Bullet {
  private:
    Vector2 position;
    Vector2 direction;
    float radius;
    float speed = 10.0f;


  public:
    Bullet();
    Bullet(Vector2 position, float radius);
    Bullet(Vector2 position, Vector2 direction, float radius);
    ~Bullet();

    Vector2 Position();

    bool IsOutOfScreen();
    void Draw();
    void Update();
    
    
};