#include "Mono.h"
#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"



Mono::Mono(Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot) :Actor(game, tag),
mDamage(100)
{
	SetACTOR(posX, posY, BoxH, BoxW, UvU, UvV, VH, VW, Rot);
	mHP = 100;
	auto SC = new SpriteComponent(this,200);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/Mono.png"));
	GetGame()->AddMono(this);
	mMygrid = GetGame()->getGrid(posX, posY);
	mMygrid->addMembersIngrid(this);
}

Mono::~Mono() {


}

void Mono::UpdateActor() 
{
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);

	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//現在のグリッドから削除
		mMygrid = newMygrid;//新たなグリッドを代入
		mMygrid->addMembersIngrid(this);//更新されたグリッドに自らを追加
	}

	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(Mono::GetPos(), 100, enemy->GetPos(), 100))
		{
			enemy->Damage(mDamage);
			Actor::SetState(EDead);
			//hit = true;
		};
	}
	Actor::mPos.y = GetPos().y;
	Actor::mPos.y += Actor::M_mlift;
	Actor::mPos.x = GetPos().x;
	Actor::SetPos(mPos.x, mPos.y);

}
