#pragma once

#include <iostream>
#include "KeyboradInput.h"
#include "Map.h"
#include "Texture.h"
#include "Vector2D.h"
#include "gameobjects/Player.h"


class GameObjects {
 public:
  //Vector2D Position;
  //Vector2D Velocity;
  //Vector2D Gravity;
  GameObjects(){};
  GameObjects(Map* map);
  ~GameObjects();
  void Init();
  void Draw();
  void Updates();
  //bool Collision(float veloX, float veloY);
  //bool OnGround();
  int ChangeScale(int size);
  void Move();
  void PlayAnimation(std::string name);

 public:
  Player* player;
 private:
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  std::map<std::string, Animation> animation;
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
  int index;
  bool animated = false;
  int AnimationSpeed = 100;
  

};
