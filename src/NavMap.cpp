#include "NavMap.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "AnimationSetter.h"

#define PI 3.1415926

NavMap* NavMap::map;

NavMap::NavMap(GameObject& associated, float tileSize, int x, int y) : Component(associated) {
	this->tileSize = tileSize;
	xsize = x;
	ysize = y;
	mapVacancy = std::vector<bool>(x*y, false);
	map = this;
	return;
}

NavMap::~NavMap() {
	map = nullptr;
	return;
}

void NavMap::Start() {
	return;
}

void NavMap::Update(float dt) {
	return;
}

void NavMap::Render() {
#ifdef DEBUG
	SDL_Point points[5];
	for (int i = 0; i < xsize; i++) {
		for (int j = 0; j < ysize; j++) {
			if (At(i, j)) {
				TileCoords block(i, j);
				Vec2 point = block.Location(tileSize).Sub(Camera::pos);
				points[0] = { (int)point.x, (int)point.y };
				points[4] = { (int)point.x, (int)point.y };
				block.x = block.x + 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[1] = { (int)point.x, (int)point.y };
				block.y = block.y + 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[2] = { (int)point.x, (int)point.y };
				block.x = block.x - 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[3] = { (int)point.x, (int)point.y };

				SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
			}
		}
	}
#endif
	return;
}

bool NavMap::Is(std::string type) {
	if (type == "NavMap") {
		return true;
	}
	return false;
}

void NavMap::Fill(TileCoords origin, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			mapVacancy[Index(origin.x + i, origin.y + j)] = true;
		}
	}
}

int NavMap::Index(int x, int y) {
	return y * xsize + x;
}

bool NavMap::At(int x, int y) {
	return mapVacancy[Index(x, y)];
}