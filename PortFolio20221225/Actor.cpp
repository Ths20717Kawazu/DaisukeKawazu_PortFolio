#pragma once
#include "Actor.h"
#include "Component.h"
#include "game.h"



Actor::Actor(Game* game)
	: mGame(game),mState(EActive)
{
	mGame->AddActor(this);
	
}

Actor::~Actor() 
{
	mGame->RemoveActor(this);

};

void Actor::AddComponent(Component* component) 
{
	mComponents.emplace_back(component);

}

void Actor::ProcessInput(void)
{
	//Playerは飛ばしてそのままComponentー＞InputComponentのProcessInputが呼び出される
	for (auto comp : mComponents) {
		comp->ProcessInput();

	}

};




