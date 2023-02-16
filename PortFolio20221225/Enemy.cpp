#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
//#include "CollisionComponent.h"

Enemy::Enemy(Game* game) :Actor(game)
{
	auto SC = new SpriteComponent(this);
	//auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/enemy.png"));
	GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){}