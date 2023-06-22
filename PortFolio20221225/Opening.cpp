#include "Opening.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"

//Opening::Opening(Game* game, enum Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot) :

Opening::Opening(Game* game, enum Tag tag):Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 100);
	SC->SetTextureID(LoadTexture((char*)"images/OPENING.png"));
}

Opening::~Opening() {};

void Opening::UpdateActor()
{};
