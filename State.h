class Sprite{
public:
	int data;
	void Render(){}
};

class Music{
public:
	int data;
};

class State{
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
private:
	Sprite bg;
	Music music;
	bool quitRequested;
};