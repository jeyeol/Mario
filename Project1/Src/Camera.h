#pragma once
#include "include/SDL2/SDL.h"
#include "Vector2D.h"

class Camera
{
 public:
  Camera(int w, int h, float speed);
  ~Camera();
  void Move();
  void MoveCentre();
  void Goto();
  void GotoCentre();
  void Update();
  Vector2D GetPosition();

 private:
  Vector2D Position;
  Vector2D Target;
  Vector2D size;
  
};

