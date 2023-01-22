#include "Actor.h"
#include "game.h"



Actor::Actor(Game* game)
	: mGame(game)
	/*, mBoxHeight(0.0f)
	, mBoxWidth(0.0f)
	, mPositionX(0.0f)
	, mPositionY(0.0f)
	, mUvpositonU(0.0f)
	, mUvpositonV(0.0f)
	, mUWidth(0.0f)
	, mVHeight(0.0f)
	, mRotation(0.0f)
	, TextureNo(0.0f)*/
{
	mGame->AddActor(this);
	
}

Actor::~Actor() {};


void Actor::AddComponent(Component* component) 
{
	mComponents.emplace_back(component);

}