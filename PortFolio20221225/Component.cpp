#pragma once
#include "Component.h"
//#include "Actor.h"



Component::Component(Actor* owner):mOwner(owner)/*,mPlayer(player*/ //, int updateOrder
	//mUpdateOrder(updateOrder)
{
	//actor��component�z���SpriteComponent��ǉ����� this�̃A�h���X��SpriteComponent���w��
	mOwner->AddComponent(this);
	
}

Component::~Component() {}
