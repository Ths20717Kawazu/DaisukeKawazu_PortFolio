#pragma once
#include "Actor.h"
#include "Player.h"

//#include "Player.h"
//#include "InputComponent.h" 

class Component
{
	public:
		Component(class Actor* Owner);
		Component(class Actor* Owner, class Player* Player);
		virtual ~Component();
		virtual void ProcessInput() {};
		virtual void Update() {};
	protected:
		class Actor* mOwner;
		class Player* mPlayer{nullptr};
};

