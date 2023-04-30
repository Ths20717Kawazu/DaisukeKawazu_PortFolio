#pragma once
#include "Component.h"
//#include "Actor.h"

Component::Component(Actor* Owner) :mOwner(Owner) 
{
	mOwner->AddComponent(this);
}

Component::Component(Actor* Owner, Player* Player):mOwner(Owner), 
mPlayer(Player)
{ 
    //actor��component�z���SpriteComponent��ǉ����� this�̃A�h���X��SpriteComponent���w��
	mOwner->AddComponent(this);	
}

Component::~Component() 
{
	mOwner->RemoveComponent(this);
}

