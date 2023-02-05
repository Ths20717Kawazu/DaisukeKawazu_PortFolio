#pragma once
#include "Component.h"
//#include "Actor.h"



Component::Component(Actor* owner):mOwner(owner)/*,mPlayer(player*/ //, int updateOrder
	//mUpdateOrder(updateOrder)
{
	//actorのcomponent配列にSpriteComponentを追加する thisのアドレスはSpriteComponentを指す
	mOwner->AddComponent(this);
	
}

Component::~Component() {}
