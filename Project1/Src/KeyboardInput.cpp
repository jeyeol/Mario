#include "Game.h"
#include "KeyboradInput.h"

void KeyboardInput::KeyControll(float& veloX, float& veloY, bool& onGround) {
  int accelation = 0;
  int maxVelocity = 15;

  if (Game::Evnt.type == SDL_KEYDOWN) {
    switch (Game::Evnt.key.keysym.sym) {
      case SDLK_UP:
         if(onGround) veloY = -20;
		 if (!onGround)
		 {
           veloY = veloY+0.75;
		 }
          break;
      case SDLK_DOWN:
        veloY = 2;
        break;
      case SDLK_RIGHT:
        veloX = 4;
        break;
      case SDLK_LEFT:
        veloX = -4;
        break;
      default:
        break;
    }
  }
  if (Game::Evnt.type == SDL_KEYUP) {
    switch (Game::Evnt.key.keysym.sym) {
      case SDLK_UP:
        break;
      case SDLK_DOWN:
        veloY = 0;
        break;
      case SDLK_RIGHT:
        veloX = 0;
        break;
      case SDLK_LEFT:
        veloX = 0;
        break;
      default:
        break;
    }
  }
}
