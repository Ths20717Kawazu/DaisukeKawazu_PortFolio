#include "Obstacle.h"
#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"



Obstacle::Obstacle(Game* game, enum Actor::Tag tag) :Actor(game, tag),
mDamage(100)
{
	mHP = 100;
	auto SC = new SpriteComponent(this,200);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/obstacle.png"));
	GetGame()->AddObstacle(this);
}

Obstacle::~Obstacle() {


}

void Obstacle::UpdateActor() 
{
	//プレイヤの移動速度を入手して、逆方向へ移動させる
//=================================================//
	D3DXVECTOR2 Pvel;
	//Playerが消滅した際に、UpdateActorが更新されなくなる不具合を下記の条件文を入れて解消する。
	//Playerの位置情報を取得し続ける部分については、この条件式が不可欠
	if (GetGame()->GetPlayer()->GetState() == Actor::EActive) 
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(Obstacle::GetPos(), 100, enemy->GetPos(), 100))
		{
			enemy->Damage(mDamage);
			Actor::SetState(EDead);
			//hit = true;
		};
	}
}
