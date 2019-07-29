#include "Texture.h"
#include "Game.h"

Texture::Texture() {}

Texture::~Texture() {}

void Texture::Init() {}

SDL_Texture* Texture::LoadTexture(const char* path) {
  SDL_Surface* tmpsurf;
  tmpsurf = IMG_Load(path);
  SDL_Texture* tex = nullptr;
  tex = SDL_CreateTextureFromSurface(Game::Rend, tmpsurf);
  if (tex == nullptr) std::cout << "texture Load failed" << std::endl;
  SDL_FreeSurface(tmpsurf);
  return tex;
}

void Texture::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect drc,
                   std::string ImageName) {
  SDL_RenderCopy(Game::Rend, tex, &src, &drc);
}

SDL_Rect Texture::ImageRect(int x, int y, int w, int h) {
  Rect_.x = x;
  Rect_.y = y;
  Rect_.w = w;
  Rect_.h = h;
  return Rect_;
}
