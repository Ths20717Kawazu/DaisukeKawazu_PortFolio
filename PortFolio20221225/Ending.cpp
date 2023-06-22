#include "Ending.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"

Ending::Ending(Game* game, enum Tag tag) :Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 100);
	SC->SetTextureID(LoadTexture((char*)"images/ENDING.png"));
}

Ending::~Ending() {};

void Ending::UpdateActor()
{};
