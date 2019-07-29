#pragma once
#include <map>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"

class Texture
{
 public:
  Texture();
  ~Texture();
  void Init();
  static SDL_Texture* LoadTexture(const char* path);
  static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect drc,
            std::string ImageName);
  SDL_Rect ImageRect(int x, int y, int w, int h); 
 //static std::map<std::string, SDL_Texture*> SpriteList;
 private:
  bool isSolid_;
  SDL_Rect Src_;
  SDL_Rect Dst_;
  SDL_Rect Rect_;
};