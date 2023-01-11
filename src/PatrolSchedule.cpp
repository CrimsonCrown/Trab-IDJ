#include "PatrolSchedule.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"

PatrolSchedule::PatrolSchedule(GameObject& associated, float tileSize) : Component(associated) {
	this->tileSize=tileSize;
	maxCommands = 9;
	currentCommand = 0;
	there = false;
	//commands
	PatrolCommand c1;
	c1.location = { 10,9 };
	c1.waitTime = 0;
	commands.push_back(c1);
	PatrolCommand c2;
	c2.location = { 10,10 };
	c2.waitTime = 0;
	commands.push_back(c2);
	PatrolCommand c3;
	c3.location = { 9,11 };
	c3.waitTime = 0;
	commands.push_back(c3);
	PatrolCommand c4;
	c4.location = { 8,11 };
	c4.waitTime = 0;
	commands.push_back(c4);
	PatrolCommand c5;
	c5.location = { 7,10 };
	c5.waitTime = 0;
	commands.push_back(c5);
	PatrolCommand c6;
	c6.location = { 7,9 };
	c6.waitTime = 0;
	commands.push_back(c6);
	PatrolCommand c7;
	c7.location = { 8,8 };
	c7.waitTime = 0;
	commands.push_back(c7);
	PatrolCommand c8;
	c8.location = { 9,8 };
	c8.waitTime = 0;
	commands.push_back(c8);
	PatrolCommand c9;
	c9.location = { 12,8 };
	c9.waitTime = 0;
	commands.push_back(c9);
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