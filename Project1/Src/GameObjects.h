#pragma once

#include <iostream>
#include "KeyboradInput.h"
#include "Map.h"
#include "Texture.h"
#include "Vector2D.h"

class GameObjects {
 public:
  Vector2D Position;
  Vector2D Velocity;
  Vector2D Gravity;
  GameObjects(){};
  GameObjects(Map* map) { this->map = map; animated=false;};
  GameObjects(Map* map, const char* path, int nframes, int mspeed);
  ~GameObjects();
  void Init(const char* path, std::string name, int x, int y, SDL_Rect Src,
            SDL_Rect DsR, int Scale);
  void Draw();
  void Updates();
  bool Collision(float veloX, float veloY);
  bool OnGround();
  int ChangeScale(int size);
  void Move();

 private:
  bool CanJump;  
  float MaxVelocity=8;
  Map* map;
  Texture texture;
  KeyboardInput Controller;
  std::string ObjectName;
  SDL_Texture* Tex;
  int speed = 3;
  SDL_Rect Src;
  SDL_Rect DsR;
  int CutRect;
  int Scale;
  int charsizeX = 16;
  int charsizeY = 16;
  bool OnGround_;  
  private: // these are variables for animation
  int frames = 0;
  bool animated = false;
  int AnimationSpeed = 100;

};
