#include "BackGround.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"

BackGround::BackGround(Game* game, enum Actor::Tag tag):Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/mori.jpg"));
}

BackGround::~BackGround() {};