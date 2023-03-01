#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"

Enemy::Enemy(Game* game, int tagID) :Actor(game, tagID)
{
	mHP = 100;
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/gorem.png"));
	GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){

	
}

void Enemy::UpdateActor() {
	mPos = Actor::GetPos();
	mPos.x += 0.5f;
	Actor::SetPos(mPos.x, mPos.y);

	count++;
	if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50)) {
		GetGame()->GetPlayer()->Damage(1.0f);
		//Actor::SetState(EDead);
		hit = true;
	};
}

void Enemy::Damage(int damage) 
{
	mHP -= damage;
	if (mHP <= 0) {
		Actor::SetState(EDead);
	}

}