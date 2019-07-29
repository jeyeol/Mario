#include "Game.h"

SDL_Renderer* Game::Rend = nullptr;
SDL_Event Game::Evnt;
SDL_Rect Game::Camera = {0, 0, 800, 640};

Game::Game() {
  Tex = new Texture();
  MapPointer = &Map_;
  Mario = new GameObjects(MapPointer, "Assets\\mario.png", 4, 100);
  // std::unique_ptr<GameObjects> Mario(new GameObjects(MapPointer));
}

Game::~Game() {
  SDL_DestroyWindow(Window);
  SDL_DestroyRenderer(Rend);
  //delete Mario;
  delete Tex;  
}
void Game::HandleEvnt() {
  SDL_PollEvent(&Evnt);
  switch (Evnt.type) {
    case SDL_QUIT:
      isRunning_ = false;
    default:
      isRunning_ = true;
      break;
  }
}

bool Game::IsRunning() { return isRunning_; }

void Game::Init(int w, int h) {
  Window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, w, h, 0);
  if (Window == nullptr) std::cout << "window failed to create" << std::endl;
  Rend = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
  if (Game::Rend == nullptr)
    std::cout << "Renderer failed to create" << std::endl;
  SDL_SetRenderDrawColor(Game::Rend, 255, 255, 255, 255);
  Map_.InitMapComponents();
  Map_.Load("Assets\\mapsprite\\TILE_INFO.txt");
  SDL_Rect MarioSRC = {80, 34, 16, 16};
  SDL_Rect MarioDst = {80, 34, 16, 16};
  Mario->Init("Assets\\mario.png", "Mario", 32, 351, MarioSRC, MarioDst, 2);
  isRunning_ = true;
}
void Game::UpdateCamera() {
  Camera.x = Mario->Position.x - 400;
  Camera.y = Mario->Position.y - 320;
  if (Camera.x < 0) Camera.x = 0;
  if (Camera.y < 0) Camera.y = 0;
}
void Game::Render() {
  SDL_RenderClear(Game::Rend);
  Map_.Draw();
  Mario->Draw();
  SDL_RenderPresent(Game::Rend);
}

void Game::Update() {
  Mario->Updates();
  UpdateCamera();
  Map_.Update();
}