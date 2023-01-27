#include "Mushroom.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "AnimationSetter.h"
#include "Pickup.h"
#include "SkillBar.h"
#include "Skill.h"

#define PI 3.1415926

Mushroom* Mushroom::player;

Mushroom::Mushroom(GameObject& associated, float tileSize) : Component(associated) {
	player = this;
	TileMover* newmover = new TileMover((associated), tileSize, 2);
	associated.AddComponent(newmover);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/chart_beta.png", 4, 2, 1, 0, 1, 0, 0);
	newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//cria alterador de sprites
	AnimationSetter* anset = new AnimationSetter((associated));
	associated.AddComponent(anset);
	//outros atributos
	hp = 3;
	currentskills=0;
	noiseRadius = 2;
	return;
}

Mushroom::~Mushroom() {
	skills.clear();
	player = nullptr;
	return;
}

void Mushroom::Start() {
	return;
}

void Mushroom::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(SDLK_1)) {
		if (currentskills >= 1) {
			//((Skill*)(skills[0].lock()->GetComponent("Skill")))->Use();
			std::shared_ptr<GameObject> skilltouse = skills[0].lock();
			if (skilltouse != nullptr) {
				((Skill*)(skilltouse->GetComponent("Skill")))->Use();
			}
		}
	}
	return;
}

void Mushroom::Render() {
	return;
}

bool Mushroom::Is(std::string type) {
	if (type == "Mushroom") {
		return true;
	}
	return false;
}

void Mushroom::NotifyCollision(GameObject& other) {
	if ((other.GetComponent("Bullet") != nullptr) && (((Bullet*)other.GetComponent("Bullet"))->targetsPlayer == true)) {
		hp -= 10;
		if (hp <= 0) {
			Camera::Unfollow();
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/penguindeath.png", 5, 0.4, 2);
			explosion->AddComponent(newspr);
			Sound* newsnd = new Sound((*explosion), "Recursos/audio/boom.wav");
			newsnd->Play();
			explosion->AddComponent(newsnd);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
			associated.RequestDelete();
		}
	}
	Pickup* pickup = (Pickup*)(other.GetComponent("Pickup"));
	if(pickup != nullptr){
		//std::cout << other.box.x << " " << other.box.y << "\n";
		if(pickup->GetType()==Pickup::HEALTH){
			hp++;
		}
		if (pickup->GetType() == Pickup::MUFFLE&&currentskills<maxskills) {
			GameObject* skill = new GameObject();
			Skill* newskill = new Skill((*skill), Skill::MUFFLE);
			skill->AddComponent(newskill);
			std::weak_ptr<GameObject> skillptr = Game::GetInstance().GetCurrentState().AddObject(skill);
			skills.push_back(skillptr);
			currentskills++;
		}
	}
	return;
}

Vec2 Mushroom::Position() {
	return associated.box.Center();
}

int Mushroom::GetHp(){
	return hp;
}

void Mushroom::Muffle(){
	noiseRadius=noiseRadius/2;
}

void Mushroom::Amplify(){
	noiseRadius=noiseRadius*2;
}

float Mushroom::NoiseRadius(){
	return noiseRadius;
}
