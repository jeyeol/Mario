#pragma once
#include <iostream>
#include "..\Animation.h"
#include "..\Map.h"
#include "..\Vector2D.h"
//#include "Collision.h"
#include <map>
#include "..\KeyboradInput.h"
#include "..\Texture.h"

class Player {
 public:
  Player(){};
  Player(Map* map);
  ~Player() {}
  void Init(const char* path, std::string name, float x, float y, int Scale);
  void Updates();
  void Draw();
  void Move();
  int SetScale(int newScale);
  void CreateAnimation();
  void PlayAnimation(std::string name);
  bool OnGround();
  bool Collision(float veloX, float veloY);
  Vector2D Position;
  Vector2D Velocity;
  Vector2D Gravity;

 private:
  // Collision collision;
  Texture texture;

 private:
  Map* map;
  SDL_Rect Src;
  int frames, speed, index;  // for animation purposes
  int m_sizeX, m_sizeY;
  SDL_Texture* Tex;
  KeyboardInput Keyboard;
  SDL_RendererFlip flip;
  int m_Scale;
  bool m_Onground;
  bool m_Animated = true;
  std::map<std::string, Animation> m_animation;
};