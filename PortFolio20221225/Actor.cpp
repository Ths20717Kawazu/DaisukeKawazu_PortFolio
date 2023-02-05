#pragma once
#include "Actor.h"
#include "Component.h"
#include "game.h"



Actor::Actor(Game* game)
	: mGame(game)

{
	mGame->AddActor(this);
	
}

Actor::~Actor() {};



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

void Actor::ActorUpdate(void) 
{
	for (auto component : mComponents)
	{
		component->Update();
	}


}


