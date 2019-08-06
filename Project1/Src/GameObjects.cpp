#include "GameObjects.h"
#include "Game.h"

GameObjects::~GameObjects() {}
GameObjects::GameObjects(Map* map) {  
  this->map = map;  
  player = &Player(this->map);
}
void GameObjects::Init() {
  player->Init("Assets\\mario.png", "Mario", 32, 351, 2);  
}

void GameObjects::Updates() { player->Updates();}
void GameObjects::Move() { player->Move();}
void GameObjects::Draw() { player->Draw();}

int GameObjects::ChangeScale(int size) {
  Scale = size;
  return Scale;
}

void GameObjects::PlayAnimation(std::string name) { }