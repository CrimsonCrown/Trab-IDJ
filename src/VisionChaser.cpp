#include "VisionChaser.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "NavMap.h"

VisionChaser::VisionChaser(GameObject& associated, float tileSize, float visionSpeed, float range) : Component(associated) {
	this->tileSize = tileSize;
	this->visionSpeed = visionSpeed;
	destinationType = LOST;
	needspath = true;
	return;
}

void VisionChaser::Update(float dt) {
	lookTimer.Update(dt);
	
    if (destinationType == SIGHT || destinationType == PATROL) {
        if (needspath) {
            //std::cout << "needs a path\n";
            float facingDirection = ((AIModule*) associated.GetComponent("AIModule"))->FacingDirection();
            if (facingDirection - destinationAngle < 0.01) {

            }
            else if (facingDirection - destinationAngle < PI/12) {
                ((AIModule*) associated.GetComponent("AIModule"))->ChangeDirection(destinationAngle, false);
            }
            else if (facingDirection < destinationAngle) {
                ((AIModule*) associated.GetComponent("AIModule"))->ShiftDirection(PI/12);   
            }
            else {
                ((AIModule*) associated.GetComponent("AIModule"))->ShiftDirection(-PI/12);
            }
            needspath = false;
        }
        if (path.empty()) {
            if (destinationType == PATROL) {
                destinationType = LOST;
            }
            else {
                destinationType = LOOKING;
                lookedDir = 0;
                lookTimer.Restart();
            }
            ((AIModule*)associated.GetComponent("AIModule"))->Stop();
            //std::cout << "no path yet\n";
        }
        else {
            nextPos = path.front();
            path.pop_front();
        }
    }
    else if (destinationType==LOOKING){
        if (lookTimer.Get() >= 0.7) {
            lookTimer.Restart();
            lookedDir++;
            if (lookedDir==1) {
                ((AIModule*)associated.GetComponent("AIModule"))->ShiftDirection(PI/2);
            }
            else if (lookedDir == 2) {
                ((AIModule*)associated.GetComponent("AIModule"))->ShiftDirection(PI);
            }
            else if (lookedDir == 3) {
                destinationType = LOST;
            }
        }
    }
	return;
}

void VisionChaser::Render() {
#ifdef DEBUG
	SDL_Point points[6];

	Vec2 point = associated.box.Center().Sub(Camera::pos);
	points[0] = { (int)point.x, (int)point.y };

	point.x+=64;
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point.x-=64;
	point.y+=64;
	points[2] = { (int)point.x, (int)point.y };

	point.x-=64;
	point.y-=64;
	points[3] = { (int)point.x, (int)point.y };

	point.x+=64;
	point.y-=64;
	points[4] = { (int)point.x, (int)point.y };

	/*point = associated.box.Center().Add(Vec2(tileSize*range,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/
	int colorR;
	int colorG;
	int colorB;
	if(destinationType==SIGHT){
		colorR=255;
		colorG=0;
		colorB=0;
	}
	else if(destinationType==PATROL){
		colorR=0;
		colorG=255;
		colorB=0;
	}
	else{
		colorR=0;
		colorG=0;
		colorB=255;
	}

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 6);
#endif
	return;
}

bool VisionChaser::Is(std::string type) {
	if (type == "VisionChaser") {
		return true;
	}
	return false;
}

void VisionChaser::See(float angle) {
	destinationType = SIGHT;
	destinationAngle = angle;
	needspath = true;
}

void VisionChaser::SeeRoute(float angle) {
	if (destinationType != SIGHT && destinationType != LOOKING) {
		if(destinationType == PATROL){
            float facingDirection = ((AIModule*) associated.GetComponent("AIModule"))->FacingDirection();
			if(facingDirection != angle){
				destinationType = PATROL;
				destinationAngle = angle;
				needspath = true;
			}
		}
		else{
			destinationType = PATROL;
			destinationAngle = angle;
			needspath = true;
		}
	}
}