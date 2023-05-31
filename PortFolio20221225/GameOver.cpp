#include "UserInterface.h"
#include "GameOver.h"
#include "texture.h"
#include "SpriteComponent.h"

GameOver::GameOver(Game* game, Actor::Tag tag) :Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 700);
	SC->SetTextureID(LoadTexture((char*)"images/GAMEOVER.png"));

}

GameOver::~GameOver() {};

void GameOver::UpdateActor()
{


}