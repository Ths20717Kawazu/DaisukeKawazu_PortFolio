#pragma once
#include "MoveComponent.h"
#include "Component.h"
//#include "Actor.h"


MoveComponent::MoveComponent(Actor* Owner) :Component(Owner)
{



}

MoveComponent::MoveComponent(Actor* Owner,  Player* Player) :Component(Owner, Player)
{



}
//MoveComponent::~MoveComponent(){ }


//void  MoveComponent::ProcessInput(void) {
//	
//
//}