#pragma once
#include "..\Map.h"
#include "..\Vector2D.h"

class Collision
{
 public:
  Collision(){};
  Collision(Map* map) { this->map = map;};
  void Init(int Scale, int CharsizeX, int CharsizeY);
  bool Logic(float veloX, float veloY, float PositionX, float PositionY, bool onGround);
  bool OnGround(int VeloX, int VeloY, int Scale, int PosX, int PosY,
                int charsizeX, int charsizeY);
 private:
  Map* map;
  Vector2D Position;
  Vector2D Velocity;
  Vector2D Gravity;
  int Scale, CharsizeX, CharsizeY;
};