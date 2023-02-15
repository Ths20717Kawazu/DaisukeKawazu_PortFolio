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
	//Player‚Í”ò‚Î‚µ‚Ä‚»‚Ì‚Ü‚ÜComponent[„InputComponent‚ÌProcessInput‚ªŒÄ‚Ño‚³‚ê‚é
	for (auto comp : mComponents) {
		comp->ProcessInput();

	}

};




