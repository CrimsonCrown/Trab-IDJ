#include "PenguinCannon.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"

#define PI 3.1415926

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated){
	//cria sprite
	Sprite* newspr=new Sprite((associated),"Recursos/img/cubngun.png");
	associated.AddComponent(newspr);
	//cria collider
	Collider* newcol=new Collider((associated));
	associated.AddComponent(newcol);
	//outros atributos
	pbody=penguinBody;
	angle=0;
	cooldown=true;
	return;
}

void PenguinCannon::Update(float dt){
	std::shared_ptr<GameObject> penguinBody=pbody.lock();
	if(penguinBody==nullptr){
		associated.RequestDelete();
		return;
	}
	//move para o centro do corpo
	associated.box=associated.box.Add(penguinBody->box.Center().Sub(associated.box.Center()));
	//calcula angulo
	float x=(float)InputManager::GetInstance().GetMouseX()+Camera::pos.x;
	float y=(float)InputManager::GetInstance().GetMouseY()+Camera::pos.y;
	Vec2 mouseposition(x,y);
	angle=mouseposition.Sub(associated.box.Center()).Incline();
	associated.angleDeg=((angle*360)/(2*PI));
	cdtimer.Update(dt);
	if(cdtimer.Get()>=0.5){
		cooldown=true;
	}
	if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)){
		if(cooldown){
			Shoot();
			cooldown=false;
			cdtimer.Restart();
		}
	}
	return;
}

void PenguinCannon::Render(){
	return;
}

bool PenguinCannon::Is(std::string type){
	if(type=="PenguinCannon"){
		return true;
	}
	return false;
}

void PenguinCannon::Shoot(){
	//cria bullet
	GameObject* bullet=new GameObject();
	Bullet* bulletCpt=new Bullet((*bullet),angle,100,10,3000,"Recursos/img/penguinbullet.png", 4, 1,false);
	bullet->AddComponent(bulletCpt);
	Vec2 bulletoffset(associated.box.w/2,0);
	bulletoffset=bulletoffset.Rotate(angle);
	bullet->box.x=(associated.box.Center().x+bulletoffset.x)-(bullet->box.w/2);
	bullet->box.y=(associated.box.Center().y+bulletoffset.y)-(bullet->box.h/2);
	//2pi=360
	//angle=x
	//(angle*360)/2pi=x
	bullet->angleDeg=((angle*360)/(2*PI));
	Game::GetInstance().GetCurrentState().AddObject(bullet);
	return;
}
