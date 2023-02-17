#include "VisionPatrol.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "VisionChaser.h"
#include <fstream>

VisionPatrol::VisionPatrol(GameObject& associated, float tileSize, std::vector<AngleCommand> commands) : Component(associated) {
	this->tileSize=tileSize;
	this->commands = commands;
	maxCommands = commands.size();
	there = false;
	currentCommand = 0;
	return;
}

void VisionPatrol::Update(float dt) {
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
		if (((AIModule* )associated.GetComponent("AIModule"))->FacingDirection() - commands[currentCommand].angle < 0.1) {
			there = true;
			timeElapsed.Restart();
		}
		else {
			((AIModule*)associated.GetComponent("AIModule"))->SeeRoute(commands[currentCommand].angle);
		}
	}
}

void VisionPatrol::Render() {
#ifdef DEBUG
	const int np=maxCommands+1;
	Vec2 point;
	SDL_Point* points=(SDL_Point*)malloc(np*sizeof(SDL_Point));

	for (int i = 0; i < maxCommands; i++) {
		point = associated.box.Center().Add(Vec2(1,1).Rotate(commands[currentCommand].angle).Mul(64*3)).Sub(Camera::pos);
		points[i] = { (int)point.x, (int)point.y };

	}
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

bool VisionPatrol::Is(std::string type) {
	if (type == "VisionPatrol") {
		return true;
	}
	return false;
}
