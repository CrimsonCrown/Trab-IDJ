#include "PatrolSchedule.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include <fstream>

PatrolSchedule::PatrolSchedule(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands) : Component(associated) {
	this->tileSize=tileSize;
	this->commands = commands;
	maxCommands = commands.size();
	there = false;
	currentCommand = 0;
	return;
}

void PatrolSchedule::Update(float dt) {
	timeElapsed.Update(dt);
	if (there) {
		if (timeElapsed.Get() >= commands[currentCommand].waitTime) {
			//std::cout << currentCommand << " is destiny\n";
			currentCommand++;
			if (currentCommand >= maxCommands) {
				currentCommand = 0;
			}
			there = false;
		}
	}
	if(!there) {
		//if (associated.box.Center().x == commands[currentCommand].location.x && associated.box.Center().y == commands[currentCommand].location.y) {
		if ((abs(associated.box.Center().x - commands[currentCommand].location.Center(tileSize).x) <(tileSize*0.1) ) && (abs(associated.box.Center().y - commands[currentCommand].location.Center(tileSize).y)<(tileSize*0.1))) {
			there = true;
			timeElapsed.Restart();
		}
		else {
			((AIModule*)associated.GetComponent("AIModule"))->Route(commands[currentCommand].location);
		}
	}
}

void PatrolSchedule::Render() {
#ifdef DEBUG
	const int np=maxCommands+1;
	Vec2 point;
	SDL_Point* points=(SDL_Point*)malloc(np*sizeof(SDL_Point));

	for (int i = 0; i < maxCommands; i++) {
		point = commands[i].location.Center(tileSize).Sub(Camera::pos);
		points[i] = { (int)point.x, (int)point.y };

	}
	point = commands[0].location.Center(tileSize).Sub(Camera::pos);
	points[maxCommands] = { (int)point.x, (int)point.y };

	/*point = associated.box.Center().Add(Vec2(tileSize*range,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, np);
	free(points);
#endif
	return;
}

bool PatrolSchedule::Is(std::string type) {
	if (type == "PatrolSchedule") {
		return true;
	}
	return false;
}
