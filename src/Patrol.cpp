#include "AIModule.h"
#include "Patrol.h"
#include <iostream>

Patrol::Patrol(GameObject& associated, std::queue<Vec2> route) : Component(associated) {
    this->route = route;
}

void Patrol::Update(float dt) {
    ((AIModule*)associated.GetComponent("AIModule"))->Route(route.front());
    route.push(route.front());
    //std::cout << std::endl << route.front().x << " " << route.front().y << std::endl;
    route.pop();
}

void Patrol::Render() {

}

bool Patrol::Is(std::string type) {
    return type == "Patrol";
}