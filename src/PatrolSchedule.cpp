#include "PatrolSchedule.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"

PatrolSchedule::PatrolSchedule(GameObject& associated) : Component(associated) {
	maxCommands = 8;
	currentCommand = 0;
	there = false;
	//commands
	PatrolCommand c1;
	c1.location = { 672,608 };
	c1.waitTime = 1;
	commands.push_back(c1);
	PatrolCommand c2;
	c2.location = { 672,672 };
	c2.waitTime = 1;
	commands.push_back(c2);
	PatrolCommand c3;
	c3.location = { 608,736 };
	c3.waitTime = 1;
	commands.push_back(c3);
	PatrolCommand c4;
	c4.location = { 544,736 };
	c4.waitTime = 1;
	commands.push_back(c4);
	PatrolCommand c5;
	c5.location = { 480,672 };
	c5.waitTime = 1;
	commands.push_back(c5);
	PatrolCommand c6;
	c6.location = { 480,608 };
	c6.waitTime = 1;
	commands.push_back(c6);
	PatrolCommand c7;
	c7.location = { 544,544 };
	c7.waitTime = 1;
	commands.push_back(c7);
	PatrolCommand c8;
	c8.location = { 608,544 };
	c8.waitTime = 1;
	commands.push_back(c8);
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
	else {
		if (associated.box.Center().x == commands[currentCommand].location.x && associated.box.Center().y == commands[currentCommand].location.y) {
			there = true;
			timeElapsed.Restart();
		}
		else {
			((AIModule*)associated.GetComponent("AIModule"))->Route(commands[currentCommand].location);
		}
	}
}

void PatrolSchedule::Render() {
	return;
}

bool PatrolSchedule::Is(std::string type) {
	if (type == "PatrolSchedule") {
		return true;
	}
	return false;
}