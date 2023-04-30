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
    //actorのcomponent配列にSpriteComponentを追加する thisのアドレスはSpriteComponentを指す
	mOwner->AddComponent(this);	
}

Component::~Component() 
{
	mOwner->RemoveComponent(this);
}

