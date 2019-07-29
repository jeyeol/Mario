#include "Game.h"
#include "include/SDL2/SDL.h"
int main(int argc, char* argv[]) {
  Game* game = &Game();
  game->Init(800, 640);
  while (game->IsRunning()) {
    float startTicks = SDL_GetTicks();
    game->HandleEvnt();
    game->Render();
    game->Update();
	float frameTicks = SDL_GetTicks() - startTicks;
    if (1000.0f / 60 > frameTicks) SDL_Delay(1000.0f / 60 - frameTicks);
  }

  return 0;
}