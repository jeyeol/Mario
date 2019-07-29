#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"

class Map {
 public:
  Map();
  ~Map();
  void InitMapComponents();
  std::vector<std::string> Load(const char* fileName);
  void Draw();
  void Update();
  SDL_Rect BackgroundRect();
  SDL_Rect SourceRect(int scaleW, int scaleH);
  SDL_Rect DestRect(int x, int y); // for a single block size
  SDL_Rect DestRectBigUnit(int scaleW, int scaleH, int x, int y); // bigger than a single unit (adjustable size)
  SDL_Rect Mario;
  bool isSolid(char tile);
  char GetTile(int x, int y);
  char SetTile(int x, int y, char tile);
  int TileX(int x);
  int TileY(int y);
  std::vector<std::string> GetMapdata();
 private:
  char block;
  std::vector<std::string> Mapdata;
  int tilesize_ = 16;
  int offset_ = 0;
  SDL_Rect Src;
  SDL_Rect Dst;
  bool Solid;
  int Scale = 2;

 private:
  SDL_Texture* smallPipe;
  SDL_Texture* LongPipe;
  SDL_Texture* itembox;
  SDL_Texture* Block;
  SDL_Texture* xBlock;
  SDL_Texture* Mario_;
  SDL_Texture* pipe;
  SDL_Texture* ground;
  SDL_Texture* background;
};