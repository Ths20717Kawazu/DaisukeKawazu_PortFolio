#include "GameStart.h"


GameStart::GameStart(Game* game, Actor::Tag tag) :Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 700);
	SC->SetTextureID(LoadTexture((char*)"images/GAMESTART.png"));

}

GameStart::~GameStart() {};

void GameStart::UpdateActor()
{
	timepassed++;
	if (timepassed >= 300) 
	{	
		SetState(Actor::EDead);
	}
}