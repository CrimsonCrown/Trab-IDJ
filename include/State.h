#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#include <iostream>
#include <string>
#include <memory>

#include "GameObject.h"

class State{
public:
	State();
	virtual ~State();
	bool QuitRequested();
	virtual void LoadAssets()=0;
	virtual void Update(float dt)=0;
	virtual void Render()=0;
	virtual void Start()=0;
	virtual void Pause()=0;
	virtual void Resume()=0;
	virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	bool PopRequested();
protected:
	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();
	bool popRequested;
	bool quitRequested;
	std::vector<std::shared_ptr<GameObject>> objectArray;
	bool started;
};

#endif