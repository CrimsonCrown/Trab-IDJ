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

Mushroom::Mushroom(GameObject& associated, float tileSize, TileCoords initialPosition, int starthp, std::vector<Skill::Type> skilltypes) : Component(associated) {
	player = this;
	TileMover* newmover = new TileMover((associated), tileSize);
	associated.AddComponent(newmover);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/mushroomtrial.png", 4, 3, 1, 0, 1, 0, 0);
	newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//cria alterador de sprites
	AnimationSetter* anset = new AnimationSetter((associated), 2, "Recursos/animations/mushroomanims.txt");
	associated.AddComponent(anset);
	//outros atributos
	this->initialPosition=initialPosition;
	this->tileSize=tileSize;
	hp = starthp;
	currentskills=0;
	noiseRadius = 3;
	tileSpeed = 2;
	Place(initialPosition);
	oldskills = skilltypes;
	invencibility = true;
	blocked=true;
	posReset = true;
	((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 1, 1);
	return;
}

Mushroom::~Mushroom() {
	skills.clear();
	player = nullptr;
	return;
}

void Mushroom::Start() {
	//skills
	for (unsigned int i = 0; i < oldskills.size(); i++) {
		Skill::Type type = oldskills[i];
		AddSkill(type);
	}
	return;
}

void Mushroom::Update(float dt) {
	deathTimer.Update(dt);
	blockTimer.Update(dt);
	replaceTimer.Update(dt);
	if(!blocked){
		if (InputManager::GetInstance().KeyPress(SDLK_i)) {
			if (currentskills >= 1) {
				//((Skill*)(skills[0].lock()->GetComponent("Skill")))->Use();
				std::shared_ptr<GameObject> skilltouse = skills[0].lock();
				if (skilltouse != nullptr) {
					((Skill*)(skilltouse->GetComponent("Skill")))->Use();
				}
			}
		}
		if (InputManager::GetInstance().KeyPress(SDLK_o)) {
			if (currentskills >= 2) {
				//((Skill*)(skills[0].lock()->GetComponent("Skill")))->Use();
				std::shared_ptr<GameObject> skilltouse = skills[1].lock();
				if (skilltouse != nullptr) {
					((Skill*)(skilltouse->GetComponent("Skill")))->Use();
				}
			}
		}
		if (InputManager::GetInstance().KeyPress(SDLK_j)) {
			if (currentskills >= 3) {
				//((Skill*)(skills[0].lock()->GetComponent("Skill")))->Use();
				std::shared_ptr<GameObject> skilltouse = skills[2].lock();
				if (skilltouse != nullptr) {
					((Skill*)(skilltouse->GetComponent("Skill")))->Use();
				}
			}
		}
	}
	else{
		if(blockTimer.Get()>=3){
			blocked=false;
			invencibility = false;
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdleLeft();
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(0, 0, 1);
		}
	}
	if (posReset) {
		if (replaceTimer.Get() >= 2) {
			Place(initialPosition);
			posReset = false;
			//sprite de volar pro inicio
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/Certo_Saindo_buraco.png", 4, 3, 1.0 / 5.0, 1, 1, 0, 5);
			newspr->SetScaleX((tileSize / explosion->box.w), (tileSize / explosion->box.h));
			explosion->AddComponent(newspr);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
		}
	}
	if (hp <= 0) {
		if (deathTimer.Get() > 1) {
			associated.RequestDelete();
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
	if (!invencibility && ((other.GetComponent("Enemy") != nullptr)||(other.GetComponent("Rat")!=nullptr))&&other.box.CenterDist(associated.box)<0.5*tileSize) {
		hp -= 1;
		if (hp <= 0) {
			Camera::Unfollow();
			deathTimer.Restart();
			blockTimer.Restart();
			blocked = true;
			invencibility = true;
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 1, 1);
			//sprite de morrer
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/Certo_morte.png", 4, 3, 1.0 / 6.0, 2, 1, 0, 6);
			newspr->SetScaleX((tileSize / explosion->box.w), (tileSize / explosion->box.h));
			explosion->AddComponent(newspr);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Sound* newsnd = new Sound((*explosion), "Recursos/audio/hit-cogumelo.wav");
			newsnd->Play(0);
			explosion->AddComponent(newsnd);
			Game::GetInstance().GetCurrentState().AddObject(explosion);
		}
		else{
			blocked = true;
			blockTimer.Restart();
			invencibility = true;
			posReset = true;
			replaceTimer.Restart();
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 1, 1);
			//sprite de tomar dano
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/Certo_dano.png", 4, 3, 2.0 / 11.0, 2, 1, 0, 10);
			newspr->SetScaleX((tileSize / explosion->box.w), (tileSize / explosion->box.h));
			explosion->AddComponent(newspr);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Sound* newsnd = new Sound((*explosion), "Recursos/audio/hit-cogumelo.wav");
			newsnd->Play(0);
			explosion->AddComponent(newsnd);
			Game::GetInstance().GetCurrentState().AddObject(explosion);
		}
	}
	if ((other.GetComponent("EndGate") != nullptr) && other.box.CenterDist(associated.box) < 0.5*tileSize) {
		blocked=true;
		blockTimer.Restart();
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 1, 1);
		invencibility = true;
	}
	Pickup* pickup = (Pickup*)(other.GetComponent("Pickup"));
	if(pickup != nullptr){
		//std::cout << other.box.x << " " << other.box.y << "\n";
		if(pickup->GetType()==Pickup::HEALTH){
			hp++;
		}
		if (pickup->GetType() == Pickup::MUFFLE&&currentskills<maxskills) {
			AddSkill(Skill::MUFFLE);
		}
		if (pickup->GetType() == Pickup::SPEEDBOOST&&currentskills < maxskills) {
			AddSkill(Skill::SPEEDBOOST);
		}
		if (pickup->GetType() == Pickup::DASH&&currentskills < maxskills) {
			AddSkill(Skill::DASH);
		}
		if (pickup->GetType() == Pickup::DECOY&&currentskills < maxskills) {
			AddSkill(Skill::DECOY);
		}
	}
	return;
}

Vec2 Mushroom::Position() {
	return associated.box.Center();
}

void Mushroom::Place(TileCoords position){
	Vec2 location=position.Location(tileSize);
	associated.box.x=location.x;
	associated.box.y=location.y;
	((TileMover*)(associated.GetComponent("TileMover")))->Reset();
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

void Mushroom::SpeedUp() {
	tileSpeed = tileSpeed * 2;
	((AnimationSetter*)associated.GetComponent("AnimationSetter"))->UpdateSpeed(tileSpeed);
}

void Mushroom::SlowDown() {
	tileSpeed = tileSpeed / 2;
	((AnimationSetter*)associated.GetComponent("AnimationSetter"))->UpdateSpeed(tileSpeed);
}

void Mushroom::Dash() {
	((TileMover*)associated.GetComponent("TileMover"))->Dash();
	invencibility = true;
}

void Mushroom::SetInvencibility(bool inv) {
	invencibility = inv;
}

float Mushroom::NoiseRadius(){
	return noiseRadius;
}

float Mushroom::TileSpeed() {
	return tileSpeed;
}

Skill* Mushroom::GetSkill(int index){
	return ((Skill*)((skills[index].lock())->GetComponent("Skill")));
}

std::vector<Skill::Type> Mushroom::GetSkillTypes() {
	std::vector<Skill::Type> skilltypes;
	for (int i = 0; i < currentskills; i++) {
		skilltypes.insert( skilltypes.end(), ((Skill*)(skills[i].lock()->GetComponent("Skill")))->GetType());
	}
	return skilltypes;
}

void Mushroom::AddSkill(Skill::Type type) {
	GameObject* skill = new GameObject();
	Skill* newskill = new Skill((*skill), type, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
	skill->AddComponent(newskill);
	std::weak_ptr<GameObject> skillptr = Game::GetInstance().GetCurrentState().AddObject(skill);
	skills.push_back(skillptr);
	if (SkillBar::bar != nullptr) {
		SkillBar::bar->AddIcon(currentskills);
	}
	currentskills++;
}

bool Mushroom::Blocked() {
	return blocked;
}