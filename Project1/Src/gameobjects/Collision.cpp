#include "Collision.h"

void Collision::Init(int Scale, int CharsizeX, int CharsizeY)
{
  this->Scale = Scale;
  this->CharsizeX = CharsizeX;
  this->CharsizeY = CharsizeY;
}

bool Collision::Logic(float veloX, float veloY, float PositionX,
                      float PositionY, bool onGround) {
  if (veloX > 0) {
    if (map->isSolid(map->GetTile(Position.x + Scale * CharsizeX + veloX,
                                  Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * CharsizeX + veloX,
                                  Position.y + Scale * CharsizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloX < 0) {
    if (map->isSolid(map->GetTile(Position.x + veloX, Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + veloX,
                                  Position.y + Scale * CharsizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloY < 0) {
    if (map->isSolid(map->GetTile(Position.x, Position.y + veloY)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * CharsizeX,
                                  Position.y + veloY)) == true) {
      return true;
      veloY = 0;
    } else
      return false;
  }
  if (veloY > 0) {
    if (map->isSolid(map->GetTile(
            Position.x, Position.y + veloY + Scale * CharsizeY)) == true ||
        map->isSolid(map->GetTile(Position.x + Scale * CharsizeX,
                                  Position.y + veloY + Scale * CharsizeY)) ==
            true) {
      return true;
      veloY = 0;
      onGround = true;
    } else
      return false;
  }
}

bool Collision::OnGround(int VeloX, int VeloY, int Scale, int PosX,
                              int PosY, int charsizeX, int charsizeY) {
  if ((VeloY > 0 && 
       map->isSolid(map->GetTile(Position.x,
                                 Position.y + Scale * charsizeY + 1))) or  //
      (Velocity.y > 0 &&
       map->isSolid(map->GetTile(Position.x + Scale * charsizeX,  // on feet
                                 Position.y + Scale * charsizeY + 1)))) {
    return true;
  } else
    return false;
}