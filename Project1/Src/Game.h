#include <iostream>
#include "Map.h"
#include "Texture.h"
#include "GameObjects.h"

class Game {
 public:
  Game();
  ~Game();
  void Init(int w, int h);
  void Render();
  void Update();
  void HandleEvnt();
  void UpdateCamera();
  bool IsRunning();
  static SDL_Renderer* Rend;
  SDL_Window* Window = nullptr;
  static SDL_Event Evnt;
  static float Timer;
  static SDL_Rect Camera;
 private:
  int Scale = 2;  
  float FPS_;
  float FrameTime_;
  bool isRunning_;

 private: //class objects
  Texture* Tex;
  Map Map_;
  Map* MapPointer;
  GameObjects* Mario;
  SDL_Texture* BackgroundMap;  
};