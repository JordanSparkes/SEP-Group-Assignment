#ifndef SCENE_H
#define SCENE_H

class SystemManager;

class Scene
{
public:
	virtual void update(SystemManager*) = 0;	//Update any objects or logic in the scene
	virtual void draw(SystemManager*, float) = 0;	//Draw everything to the screen
	virtual void load(SystemManager*) = 0;	//load all the data and assets the scene needs
	virtual void unload(SystemManager*) = 0;	//Unload everything when leaving the scene
};

#endif