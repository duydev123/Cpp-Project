#include "raylib.h"
#include <vector>
#include <iostream>

int main()
{
   // Khởi tạo kích thước cửa sổ
   const float screenWidth = 1920.0f;
   const float screenHeight = 1080.0f;
   float framecounter = 0.0f;
   float boostcouter = 20.0f;
   float spawntime = 90.0f;
   float speed = 11.0f;
   float jumpspeed = -8.0f;

   float  pipegap = 320;
   int score = 0;

   std::vector<Rectangle> pipes;
   std::vector<Rectangle> middlepipes;
   std::vector<bool> middlecollision;

   Rectangle player = {screenWidth / 4, screenHeight / 2 - 60, 60.0f, 60.0f};

   bool isboost = false;
   bool isgameover = false;
   bool isgamestart = false;


   const char *gametitle = "Flappy Bird";
   const char *gameovertitle = "Game Over !";

   InitWindow(screenWidth, screenHeight, "Raylib VSCode Test");
   InitAudioDevice();

   Sound hitsound = LoadSound("Sounds/hit.wav");
   Sound jumpsound = LoadSound("Sounds/jump.mp3");
   Sound fallsound = LoadSound("Sounds/fall.mp3");
   Sound pointsound = LoadSound("Sounds/point.mp3");


   Vector2 titlesize = MeasureTextEx(GetFontDefault(), gametitle, 108, 2);
   Vector2 gameoversize = MeasureTextEx(GetFontDefault(), gameovertitle, 126, 2);

   auto playerdead = [&]()
   {
      isgamestart = false;
      isgameover = true;
      pipes.clear();
      middlepipes.clear();
      middlecollision.clear();
      player.y = screenHeight / 2 - 70.0f;
      framecounter = 0;
   };

   SetTargetFPS(60);
   

   while (!WindowShouldClose()) 
   {
      float fps = GetFPS();


      if ((GetKeyPressed() != 0 || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && !isgamestart)
      {
         score = 0;
         isgameover = false;
         isgamestart = true;
      }

      if(isgamestart) {
         framecounter++;
         boostcouter--;
         if(player.y >= screenHeight) {
            PlaySound(fallsound);
            playerdead();
         }
         if (framecounter >= spawntime)
         {
            float pipeposY = GetRandomValue(-720, 0);
            Rectangle topPipe = {screenWidth - 180, pipeposY, 60.0f, 820.0f};
            Rectangle bottomPipe = {screenWidth - 180, pipeposY + topPipe.height + pipegap, 60.0f, 820.0f};
            Rectangle middlePipe = { screenWidth - 180, pipeposY + topPipe.height + 5, 60.0f, pipegap - 5 };
            pipes.push_back(topPipe);
            pipes.push_back(bottomPipe);
            middlepipes.push_back(middlePipe);
            middlecollision.push_back(false);
            framecounter = 0;
         }

         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
         {
            isboost = true;
            boostcouter = 20.0f;
            PlaySound(jumpsound);
         }
         if (boostcouter < 0)
         {
            isboost = false;
         }
         if (isboost)
         {
            player.y += jumpspeed;
         }
         else
         {
            player.y += speed;
         }

         for (int i = 0; i < pipes.size(); i++)
         {
            if (CheckCollisionRecs(player, pipes[i]))
            {
               PlaySound(hitsound);
               playerdead();
            }
            pipes[i].x -= 4;
            if (pipes[i].x < -60)
            {
               pipes.erase(pipes.begin() + i);
               i--;
            }
         }
         for (int i = 0 ; i < middlepipes.size(); i++) 
         {
            middlepipes[i].x -= 4;
            if (middlepipes[i].x < -60)
            {
               middlepipes.erase(middlepipes.begin() + i);
               middlecollision.erase(middlecollision.begin() + i);
               i--;
            }
            if (CheckCollisionRecs(player, middlepipes[i]) && middlecollision[i] == false)
            {
               middlecollision[i] = true;
               score++;
               PlaySound(pointsound);
            }
         }
      }
      BeginDrawing();   

      ClearBackground(RAYWHITE);

      for (int i = 0; i < 32; i++)
      {
         for (int j = 0; j < 18; j++)
         {
            DrawRectangleLines(i * 60, j * 60, 60, 60, RED);
         }
      }

      if(isgamestart) {
         for (int i = 0; i < pipes.size(); i++)
         {
            DrawRectangleRec(pipes[i], RED);
         }
         DrawText(TextFormat("Score: %i", score) , 12, 68, 32, BLACK);
      }
      else if (isgameover) {
         DrawTextEx(GetFontDefault(), gameovertitle, {screenWidth / 2 - gameoversize.x / 2, 168}, 136, 2, BLACK);
         DrawText(TextFormat("Score: %i", score), screenWidth / 2 - 120, screenHeight / 2 - 170, 48, BLACK);
         if (((int)(GetTime() * 2) % 2) == 0)
         {
            DrawText("PRESS ANY KEY TO START AGAIN !", screenWidth / 2 - 320, screenHeight / 2 - 48, 36, RED);
         }
      }
      else {
         DrawTextEx(GetFontDefault(), gametitle, {screenWidth / 2 - titlesize.x / 2, 108}, 108, 2, BLACK);

         if (((int)(GetTime() * 2) % 2) == 0)
         {
            DrawText("PRESS ANY KEY TO START", screenWidth / 2 - 240, screenHeight / 2 - 30, 36, RED);
         }
      }

      DrawRectangleRec(player, GREEN);


      DrawText(TextFormat("%.0f FPS", fps), 12, 12, 32, GREEN);

      EndDrawing();
   }
   CloseAudioDevice();
   CloseWindow();

   return 0;
}
