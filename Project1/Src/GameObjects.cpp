#include "GameObjects.h"
#include "Game.h"

GameObjects::~GameObjects() {}
GameObjects::GameObjects(Map* map, const char* path, int nframes, int mspeed) {
  animated = true;
  this->map = map;
  frames = nframes;
  AnimationSpeed = mspeed;
  Tex = Texture::LoadTexture(path);
}
void GameObjects::Init(const char* path, std::string name, int x, int y,
                       SDL_Rect Src, SDL_Rect DsR, int Scale) {
  this->Scale = Scale;
  Position.x = x;
  Position.y = y;
  this->Src = Src;
  this->DsR = DsR;
  this->DsR = {static_cast<int>(Position.x), static_cast<int>(Position.y),
               Scale * charsizeX, Scale * charsizeY};
  ObjectName = name;
  Tex = Texture::LoadTexture(path);
  Gravity.x = 0;
  Gravity.y = 1.0f;
}

void GameObjects::Updates() {
  Controller.KeyControll(Velocity.x, Velocity.y, OnGround_);
  Move();
}
void GameObjects::Move() {
  if (Velocity.y > MaxVelocity) Velocity.y = MaxVelocity;
  if (Position.x < 0) Position.x = 0;
  if (Position.y < 0) Position.y = 0;
  OnGround_ = OnGround();
  if (!OnGround()) Velocity.y += Gravity.y;

  if (!Collision(Velocity.x, 0)) {
    Position.x += Velocity.x;
  }

  if (!Collision(0, Velocity.y)) {
    Position.y += Velocity.y;
  }
  if (Collision(Velocity.x, 0)) {
    Velocity.x = 0;
  }

  if (Collision(0, Velocity.y)) {
    Velocity.y = 0;
  }
}
void GameObjects::Draw() {
  float startTick = SDL_GetTicks();
  if (!animated)
    Texture::Draw(Tex, Src,
                  texture.ImageRect(Position.x - Game::Camera.x, Position.y,
                                    Scale * charsizeX, Scale * charsizeY),
                  ObjectName);
  
  if (animated)
    Texture::Draw(Tex,
                  texture.ImageRect(Src.x + 17 * 
                          static_cast<int>((SDL_GetTicks()/ AnimationSpeed) % frames),
                      Src.y, Src.w, Src.h),
                  texture.ImageRect(Position.x - Game::Camera.x, Position.y,
                                    Scale * charsizeX, Scale * charsizeY),
                  ObjectName);
}
bool GameObjects::OnGround() {
  if ((Velocity.y > 0 &&
       map->isSolid(map->GetTile(Position.x,
                                 Position.y + Scale * charsizeY + 1))) or  //
      (Velocity.y > 0 &&
       map->isSolid(map->GetTile(Position.x + Scale * charsizeX,  // on feet
                                 Position.y + Scale * charsizeY + 1)))) {
    return true;
  } else
    return false;
}

bool GameObjects::Collision(float veloX, float veloY) {
  if (veloX > 0) {
    if (map->isSolid(map->GetTile(Position.x + Scale * charsizeX + veloX,
                                  Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * charsizeX + veloX,
                                  Position.y + Scale * charsizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloX < 0) {
    if (map->isSolid(map->GetTile(Position.x + veloX, Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + veloX,
                                  Position.y + Scale * charsizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloY < 0) {
    if (map->isSolid(map->GetTile(Position.x, Position.y + veloY)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * charsizeX,
                                  Position.y + veloY)) == true) {
      return true;
      veloY = 0;
    } else
      return false;
  }
  if (veloY > 0) {
    if (map->isSolid(map->GetTile(
            Position.x, Position.y + veloY + Scale * charsizeY)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * charsizeX,
                                  Position.y + veloY + Scale * charsizeY)) ==
            true) {
      return true;
      veloY = 0;
      OnGround_ = true;
    } else
      return false;
  }
}
int GameObjects::ChangeScale(int size) {
  Scale = size;
  return Scale;
}
