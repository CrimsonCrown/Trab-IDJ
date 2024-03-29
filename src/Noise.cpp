#include "Noise.h"
#include "Collider.h"
#include "Game.h"
#include "Mushroom.h"

#define PI 3.1415926

Noise::Noise(GameObject& associated, Vec2 origin, float radius, std::string soundfile) : Component(associated){
	Collider* newcol=new Collider(associated);
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/Sound_complete.png", 4, 1, duration/3.0, duration, 1, 1, 3);
	associated.AddComponent(newspr);
	//cria som
	Sound* newsnd = new Sound((associated), soundfile);
	newsnd->Play();
	associated.AddComponent(newsnd);
	dtacc = 0;
	this->origin=origin;
	this->radius=radius;
	associated.box.w=radius*2*((1.0/duration)*dtacc);
	associated.box.h=radius*2*((1.0 / duration)*dtacc);
	associated.box.x=origin.x-radius;
	associated.box.y=origin.y-radius;
	return;
}

void Noise::Update(float dt){
	dtacc += dt;
	associated.box.w = radius * 2 * ((1.0 / duration)*dtacc);
	associated.box.h = radius * 2 * ((1.0 / duration)*dtacc);
	associated.box.x = origin.x - radius * ((1.0 / duration)*dtacc);
	associated.box.y = origin.y - radius * ((1.0 / duration)*dtacc);
}

void Noise::Render(){
#ifdef DEBUG
	const int np=24;
	float direction=0;
	SDL_Point points[np];

	for (int i = 0; i < np; i++) {
		Vec2 point = associated.box.Center().Add(Vec2(radius, 0).Rotate((direction - PI) + (i*((2*PI)/(np-1))))).Sub(Camera::pos);
		points[i] = { (int)point.x, (int)point.y };

	}

	/*point = associated.box.Center().Add(Vec2(tileSize*range,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, np);
#endif
}

bool Noise::Is(std::string type){
	if(type=="Noise"){
		return true;
	}
	return false;
}

Vec2 Noise::GetOrigin() {
	return origin;
}
	
float Noise::GetRadius() {
	return radius;
}