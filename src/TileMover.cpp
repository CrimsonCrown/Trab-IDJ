#include "TileMover.h"
#include "Game.h"

TileMover::TileMover(GameObject& associated) : Component(associated) {
	state = RESTING;
	return;
}

void TileMover::Update(float dt) {
	if (state == RESTING) {
		Vec2 offset = { 0,0 };
		bool moved = false;
		destination = associated.box.Center();
		if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
			offset.y -= 64;
			moved = true;
		}
		else if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
			offset.y += 64;
			moved = true;
		}
		else if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
			offset.x -= 64;
			moved = true;
		}
		else if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
			offset.x += 64;
			moved = true;
		}
		if (moved) {
			state = MOVING;
			destination=destination.Add(offset);
		}
	}
	if (state == MOVING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = 64 * dt;
		if (destination.DistTo(boxPos) <= distToMove) {
			associated.box.x = destination.x - (associated.box.w / 2);
			associated.box.y = destination.y - (associated.box.h / 2);
		}
		else {
			speed = destination.Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(destination) == 0) {
			state = RESTING;
		}
	}
	return;
}

void TileMover::Render() {
	return;
}

bool TileMover::Is(std::string type) {
	if (type == "TileMover") {
		return true;
	}
	return false;
}