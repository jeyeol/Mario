#include "Player.h"
#include "..\Game.h"

Player::Player(Map* map) {  
  this->map = map; 
 // collision = Collision(this->map);
  m_sizeX = 16;
  m_sizeY = 16;
  m_Scale = 2;
  Gravity.x = 0;
  Gravity.y = 1.0f;
  Src = {80, 34, 16, 16};
  
}

void Player::Init(const char* path, std::string name, float x, float y,
                  int Scale) {
  //collision.Init(m_Scale, m_sizeX, m_sizeY);
  Position.x = x;
  Position.y = y;
  m_Scale = Scale;
  Tex = Texture::LoadTexture(path); 
  CreateAnimation();
}
void Player::Move() {
  float MaxVelocity = 15.0f;
  if (Velocity.y > MaxVelocity) Velocity.y = MaxVelocity;
  if (Position.x < 0) Position.x = 0;
  if (Position.y < 0) Position.y = 0;
  m_Onground = OnGround();
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

void Player::Updates() {
  Keyboard.KeyControll(Velocity.x, Velocity.y, m_Onground);
  Move();
  if (Velocity.x == 0 && Velocity.y == 0)
    m_Animated = false;
  else
    m_Animated = true;
  if (Velocity.x > 0) flip = SDL_FLIP_NONE;
}
void Player::Draw() {
  m_Onground = Collision(Velocity.x, Velocity.y);	  
	  //collision.OnGround(Velocity.x, Velocity.y, m_Scale,
        //                           Position.x,
          //                         Position.y, m_sizeX, m_sizeY);
  if (!m_Animated)
    Texture::Draw(Tex, Src,
                  texture.ImageRect(Position.x - Game::Camera.x, Position.y,
                                    m_Scale * m_sizeX, m_Scale * m_sizeY),
                  "mario", flip);
  if (m_Animated && Velocity.x > 0 && Velocity.y == 0) PlayAnimation("left");
  if (m_Animated && Velocity.y != 0) PlayAnimation("up");
  if (m_Animated && Velocity.x < 0 && Velocity.y == 0) PlayAnimation("right");
}

int Player::SetScale(int newScale) {
  m_Scale = newScale;
  return m_Scale;
}

void Player::CreateAnimation() {
  Animation Left = Animation(17, 4, 100);     // mario motion ani
  Animation Up = Animation(17 * 5, 2, 5000);  // mario motion ani
  Animation Right = Animation(-17, 4, 100);
  m_animation.emplace("left", Left);  // push to map
  m_animation.emplace("up", Up);      // push to map
  m_animation.emplace("right", Right);
}

void Player::PlayAnimation(std::string name)
{
  frames = m_animation[name].frames;
  speed = m_animation[name].speed;
  index = m_animation[name].index;
  float startTick = SDL_GetTicks();
  if (index < 0) {
    flip = SDL_FLIP_HORIZONTAL;
    index *= -1;
  }
  Texture::Draw(
      Tex,
      texture.ImageRect(
          Src.x + index * static_cast<int>((SDL_GetTicks() / speed) %
                                           frames),
          Src.y, Src.w, Src.h),
      texture.ImageRect(Position.x - Game::Camera.x, Position.y,
                        m_Scale * m_sizeX, m_Scale * m_sizeY),
      "Mario", flip);
  if (name == "up") {
    SDL_Rect SrcUp = {165, 34, Src.w, Src.h};
    Texture::Draw(Tex, SrcUp,
                  texture.ImageRect(Position.x - Game::Camera.x, Position.y,
                                    m_Scale * m_sizeX, m_Scale * m_sizeY),
                  "Mario", flip);
  }
}

bool Player::OnGround()
{
  if ((Velocity.y > 0 &&
       map->isSolid(map->GetTile(Position.x,
                                 Position.y + m_Scale * m_sizeY + 1))) or  //
      (Velocity.y > 0 &&
       map->isSolid(map->GetTile(Position.x + m_Scale * m_sizeX,  // on feet
                                 Position.y + m_Scale * m_sizeY + 1)))) {
    return true;
  } else
    return false;
}
bool Player::Collision(float veloX, float veloY)
{
  if (veloX > 0) {
    if (map->isSolid(map->GetTile(Position.x + m_Scale * m_sizeX + veloX,
                                  Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + m_Scale * m_sizeX + veloX,
                                  Position.y + m_Scale * m_sizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloX < 0) {
    if (map->isSolid(map->GetTile(Position.x + veloX, Position.y)) == true ||
        map->isSolid(map->GetTile(Position.x + veloX,
                                  Position.y + m_Scale * m_sizeY)) == true) {
      return true;
      veloX = 0;
    } else
      return false;
  }
  if (veloY < 0) {
    if (map->isSolid(map->GetTile(Position.x, Position.y + veloY)) == true ||
        map->isSolid(map->GetTile(Position.x + m_Scale * m_sizeX,
                                  Position.y + veloY)) == true) {
      return true;
      veloY = 0;
    } else
      return false;
  }
  if (veloY > 0) {
    if (map->isSolid(map->GetTile(
            Position.x, Position.y + veloY + m_Scale * m_sizeY)) == true ||
        map->isSolid(map->GetTile(Position.x + m_Scale * m_sizeX,
                                  Position.y + veloY + m_Scale * m_sizeY)) ==
            true) {
      return true;
      veloY = 0;
      m_Onground = true;
    } else
      return false;
  }
}