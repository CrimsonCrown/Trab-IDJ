#include "TileMover.h"
#include "Game.h"
#include "AnimationSetter.h"
#include "Noise.h"
#include "Mushroom.h"

TileMover::TileMover(GameObject& associated, float tileSize) : Component(associated) {
	this->tileSize = tileSize;
	state = RESTING;
	return;
}

void TileMover::Update(float dt) {
	if (state == RESTING) {
		Vec2 offset = { 0,0 };
		bool moved = false;
		destination = associated.box.Center();
		if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
			offset.y -= tileSize;
			moved = true;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
			offset.y += tileSize;
			moved = true;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
			offset.x -= tileSize;
			moved = true;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
			offset.x += tileSize;
			moved = true;
		}
		if (moved) {
			state = MOVING;
			destination=destination.Add(offset);
			float facingDirection=offset.Incline();
			if (facingDirection < 0) {
				facingDirection += 2 * PI;
			}
			if (facingDirection > 13 * (PI / 8) || facingDirection < 3 * (PI / 8)) {
				//direita
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunRight();
			}
			else if (facingDirection > 5 * (PI / 8) && facingDirection < 11 * (PI / 8)) {
				//esquerda
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunLeft();
			}
			else if (facingDirection > 3 * (PI / 8) && facingDirection < 5 * (PI / 8)) {
				//baixo
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunRight();
			}
			else if (facingDirection > 11 * (PI / 8) && facingDirection < 13 * (PI / 8)) {
				//cima
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunLeft();
			}
		}
		else{
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdle();
		}
	}
	if (state == MOVING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = tileSize * Mushroom::player->TileSpeed() * dt;
		if (destination.DistTo(boxPos) <= distToMove) {
			associated.box.x = destination.x - (associated.box.w / 2);
			associated.box.y = destination.y - (associated.box.h / 2);
		}
		else {
			Vec2 speed = destination.Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(destination) == 0) {
			state = RESTING;
			//faz barulho
			GameObject* noise=new GameObject();
			Noise* newnoise=new Noise((*noise), associated.box.Center(), tileSize*Mushroom::player->NoiseRadius());
			noise->AddComponent(newnoise);
			Game::GetInstance().GetCurrentState().AddObject(noise);
		}
	}
	if (state == DASHING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = tileSize * 4 * Mushroom::player->TileSpeed() * dt;
		if (destination.DistTo(boxPos) <= distToMove) {
			associated.box.x = destination.x - (associated.box.w / 2);
			associated.box.y = destination.y - (associated.box.h / 2);
		}
		else {
			Vec2 speed = destination.Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(destination) == 0) {
			state = RESTING;
			Mushroom::player->SetInvencibility(false);
			//faz barulho alto
			GameObject* noise=new GameObject();
			Noise* newnoise=new Noise((*noise), associated.box.Center(), tileSize*Mushroom::player->NoiseRadius() * 2);
			noise->AddComponent(newnoise);
			Game::GetInstance().GetCurrentState().AddObject(noise);
		}
	}
	return;
}

void TileMover::Dash() {
	Vec2 offset = { 0,0 };
	if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
		offset.y -= tileSize;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		offset.y += tileSize;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
		offset.x -= tileSize;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		offset.x += tileSize;
	}
	destination=destination.Add(offset.Mul(2));
	state = DASHING;
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

void TileMover::Reset(){
	state=RESTING;
}