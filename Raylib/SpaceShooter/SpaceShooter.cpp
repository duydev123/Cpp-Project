#include <raylib.h> 
#include <vector>
#include <iostream>
#include "Entities/Player/player.h"
#include "Entities/Bullet/bullet.h"
#include "Entities/Enemy/gunship.h"

int main() {

  const float screenWidth = 1920;
  const float screenHeight = 1080;
  const float enemySpawnRate = 180.0f; //frame
  float enemySpawnTimer = 0.0f;

  const int gridWidth = 60;
  const int gridHeight = 60;

  bool gameOver = false;
  bool gridSlot[15][4] = {0};

  Player player = {{screenWidth / 2 - 60, 900}, {60, 60}};

  std::vector<Bullet> playerBullets;
  std::vector<Bullet> gunShipBullets;
  std::vector<GunShip> gunShips;
  
  

  InitWindow(screenWidth, screenHeight, "SpaceShooter");
  InitAudioDevice();
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    float frametime = GetFrameTime();
    enemySpawnTimer++;

    if(enemySpawnTimer >= enemySpawnRate) {
      enemySpawnTimer = 0;
      std::vector<Vector2> emptySlots;
      for (int i = 0; i < 15; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          if (gridSlot[i][j] == false)
          {
            Vector2 slot = {(float)i, float(j)};
            emptySlots.push_back(slot);
          }
        }
      }
      for (int i = 0; i < 4 && !emptySlots.empty(); i++) {
        int randomIndex = GetRandomValue(0, emptySlots.size() - 1);
        GunShip newGunShip = {{ float(GetRandomValue(0, 1920)), -70 }, {60, 60}};
            newGunShip.TargetSlot(emptySlots[randomIndex]);
            gridSlot[int(emptySlots[randomIndex].x)][int(emptySlots[randomIndex].y)] = true;
            gunShips.push_back(newGunShip);
        }
      }
    

    player.Update(frametime);
    for (int i = 0; i < playerBullets.size(); i++)
    {
      playerBullets[i].Update();
      if (playerBullets[i].IsOutOfScreen())
      {
        playerBullets.erase(playerBullets.begin() + i);
        i--;
        break;
      }
      for (int j = 0; j < gunShips.size(); j++ ){
        if (CheckCollisionCircleRec(playerBullets[i].Position(), 8, {gunShips[j].Position().x, gunShips[j].Position().y, 60, 60}))
        {
          Vector2 slot = gunShips[j].TargetSlot();
          gridSlot[(int)slot.x][(int)slot.y] = false;
          gunShips.erase(gunShips.begin() + j);
          j--;
          playerBullets.erase(playerBullets.begin() + i);
          i--;
        }
      }
    }
    for (int i = 0; i < gunShipBullets.size(); i++)
    {
      gunShipBullets[i].Update();
      if(gunShipBullets[i].IsOutOfScreen()) {
        gunShipBullets.erase(gunShipBullets.begin() + i);
        i--;
      }
      if (CheckCollisionCircleRec(gunShipBullets[i].Position(), 8, {player.Position().x, player.Position().y, 60, 60}))
      {
        gameOver = true;
        gunShipBullets.clear();
      }
    }

    for (GunShip &ship : gunShips)
    {
      ship.Update(frametime);
      if(ship.CanShoot()) {
        gunShipBullets.push_back(ship.Shoot(ship.CalculateDirection(player.Position())));
        ship.ResetShootTimer();
      }
    }


    if(IsKeyDown(KEY_SPACE) && player.CanShoot()) {
      playerBullets.push_back(player.Shoot());
      player.ResetShootTimer();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for(Bullet &bullet : playerBullets) {
      bullet.Draw();
    }
    for (Bullet &bullet : gunShipBullets)
    {
      bullet.Draw();
    }
    for(GunShip &ship : gunShips) {
      ship.Draw();
    }
    player.Draw();
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}