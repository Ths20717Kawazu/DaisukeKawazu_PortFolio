#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"

Enemy::Enemy(Game* game) :Actor(game)
{
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/gorem.png"));
	GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){
	
}




void Enemy::UpdateActor() {
	float posx;
	float posy;
	posx = Actor::GetPos().x;
	posy = Actor::GetPos().y;
	posx += 1.0f;
	Actor::SetPos(posx, posy);

	count++;
	if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50)) {
		Actor::SetState(EDead);
		hit = true;
	
	};

}