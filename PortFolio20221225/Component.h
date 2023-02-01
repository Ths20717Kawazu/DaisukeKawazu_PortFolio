#pragma once
#include "Actor.h"
//#include "Player.h"
//#include "InputComponent.h" 

class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();
	virtual void ProcessInput() {};
protected:
	class Actor* mOwner;

};

