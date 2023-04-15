#include "game.h"
#include "Block.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "texture.h"


Block::Block(Game* game, enum Actor::Tag tag) : Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/Block.png"));
	GetGame()->AddBlock(this);
}