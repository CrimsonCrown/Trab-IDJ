#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& associated) : associated(associated){
	return;
}

Component::~Component(){
	return;
}

