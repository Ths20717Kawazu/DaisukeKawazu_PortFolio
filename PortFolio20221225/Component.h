#pragma once
#include "Actor.h"


//#include "Player.h"
//#include "InputComponent.h" 

class Component
{
public:
	Component(class Actor* owner);
	//Component(class Actor* owner, class Player* player);
	virtual ~Component();
	virtual void ProcessInput() {};
	virtual void Update() {};
protected:
	class Actor* mOwner;
	//class Player* mPlayer;

};

