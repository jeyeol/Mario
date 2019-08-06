#include "Map.h"
#include "Game.h"
#include "Texture.h"

Map::Map() { int x = 95; }

void Map::InitMapComponents() {
  itembox = Texture::LoadTexture("Assets\\mapsprite\\itembox.png");
  Block = Texture::LoadTexture("Assets\\mapsprite\\brownblock.png");
  xBlock = Texture::LoadTexture("Assets\\mapsprite\\box.png");
  ground = Texture::LoadTexture("Assets\\mapsprite\\groundtile.png");
  background = Texture::LoadTexture("Assets\\mapsprite\\deletedmap.png");
  smallPipe = Texture::LoadTexture("Assets\\mapsprite\\pipe32X32.png");
  LongPipe = Texture::LoadTexture("Assets\\mapsprite\\pipe32X64.png");
}

Map::~Map() {}

SDL_Rect Map::SourceRect(int scaleW, int scaleH) {
  Src.h = scaleH*16;
  Src.w = 16 * scaleW;
  Src.x = Src.y = 0;
  return Src;
}
SDL_Rect Map::DestRect(int x, int y) {
  Dst.h = Dst.w = 16 * Scale;
  Dst.x = x * tilesize_ * Scale - Game::Camera.x;
  Dst.y = Scale * y * tilesize_;
  return Dst;
}
SDL_Rect Map::DestRectBigUnit(int scaleW, int scaleH, int x, int y) {
  SDL_Rect Rect;
  Rect.h = 16* scaleH;
  Rect.w = 16 * scaleW;
  Rect.x = x * tilesize_ * Scale - Game::Camera.x;
  Rect.y = Scale * y * tilesize_;
  return Rect;
}

std::vector<std::string>& Map::Load(const char* fileName) {
  std::ifstream file;
  file.open(fileName);
  if (file.fail()) {
    perror(fileName);
    system("PAUSE");
    std::cout << "Map file failed to load" << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(file, line)) {
    Mapdata.push_back(line);
  }
  file.close();
  return Mapdata;
  
}
bool Map::isSolid(char tile) {
  if (tile != '.')
    return true;
  else
    return false;
}
SDL_Rect Map::BackgroundRect() {
  SDL_Rect Rect; 
  Rect.x = 0;
  Rect.y = 0;
  Rect.w = 3392*Scale;
  Rect.h = 920;
  return Rect;
}
void Map::Draw() {
  SDL_Rect Srt1 = {0-Game::Camera.x, 0, 3392, 460};
  SDL_Rect Drt1 = {0-Game::Camera.x, 0, 3392*Scale, 460*Scale};

  Texture::Draw(background, BackgroundRect(), Drt1, "Background", flip);

  for (int i = 0; i < Mapdata.size(); i++) {
    for (int j = 0; j < Mapdata[i].size(); j++) {
      block = Mapdata[i][j];
      switch (block) {
        case '?':
          Texture::Draw(itembox, SourceRect(1, 1), DestRect(j, i), "itembox", flip);
          break;
        case 'b':
          Texture::Draw(Block, SourceRect(1, 1), DestRect(j, i), "block",
                        flip);  // brown block
          break;
        case 'x':
          Texture::Draw(xBlock, SourceRect(1, 1), DestRect(j, i), "xblock",
                        flip);
          break;
        case 'g':
          Texture::Draw(ground, SourceRect(1, 1), DestRect(j, i), "ground",
                        flip);
          break;
        case '.':
          Solid = false;
          break;
        case 'p':
          Texture::Draw(smallPipe, SourceRect(2, 2),
                        DestRectBigUnit(4, 4, j, i), "shortPipe", flip);
          break;
        case 'P':
          Texture::Draw(smallPipe, SourceRect(2,2),
                        DestRectBigUnit(4, 6, j, i), "longPipe", flip);
          break;
        default:
          Solid = false;
          break;
      }
    }
  }
}

void Map::Update() {  }

char Map::GetTile(int x, int y) {
  int X, Y;
  X = x / (tilesize_ * Scale);
  Y = y / (Scale * tilesize_);
  return Mapdata[Y][X];
}

char Map::SetTile(int x, int y, char tile) {
  int X, Y;
  X = x / (tilesize_ * Scale);
  Y = y / (Scale * tilesize_);
  tile = Mapdata[X][Y];
  return tile;
}

int Map::TileX(int x) {
  int X;
  X = x / (tilesize_ * Scale);
  return X;
}

int Map::TileY(int y) {
  int Y;
  Y = (y - Scale * offset_) / (Scale * tilesize_);
  return Y;
}

std::vector<std::string> Map::GetMapdata() { return Mapdata; }
