#ifndef AIMODULE_INCLUDE
#define AIMODULE_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Minion.h"
#include "TileCoords.h"
#include "PatrolSchedule.h"
#include "VisionPatrol.h"

class AIModule : public Component {
public:
	AIModule(GameObject& associated, float tileSize, float facingDirection = 0);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void AddVision(float range, float angle);
	void AddChaser(float tileSpeed);
	void AddVisionChaser(float tileSpeed, float range);
	void AddPatrol(std::vector<PatrolCommand> commands);
	void AddVisionPatrol(std::vector<AngleCommand> commands);
	void AddHearing(float radius);
	void AddAnimations(float tileSpeed, std::string name);
	void AddScreamer(float noiseRadius);
	void See(Vec2 location);
	void Hear(Vec2 location);
	void Smell(Vec2 location);
	void Route(TileCoords location);
	void SeeRoute(float angle);
	float FacingDirection();
	void ChangeDirection(float newdir, bool moving=true);
	void ShiftDirection(float newdir, bool moving=false);
	void Stop();
	void Spooked();
private:
	float facingDirection;
	float tileSize;
	bool vision;
	bool chaser;
	bool visionChaser;
	bool patrol;
	bool visionPatrol;
	bool hearing;
	bool animations;
	bool screamer;
};

#endif