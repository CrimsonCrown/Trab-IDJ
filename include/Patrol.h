#ifndef PATROL_H
#define PATROL_H

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"

class Patrol : public Component {
public:
    Patrol(GameObject& associated, std::queue<Vec2> route);
    void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
    std::queue<Vec2> route;
};

#endif