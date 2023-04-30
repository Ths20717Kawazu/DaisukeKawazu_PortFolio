#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, enum Actor::Tag tag): Actor(game, tag),
mLift(5.0f),
mDamage(100)
{
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	SetOwner(GetGame()->GetPlayer());
	animate = false;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(-2.03f);//プレイヤに浮力を与える
	GetGame()->AddBalloon(this);
}

Balloon::~Balloon() 
{	
	GetGame()->GetPlayer()->SetLift(0.0f);
	GetGame()->GetPlayer()->SetHasballoon(false);
	//int tag = Actor::GetTag();
	//tag--;
	//Actor::SetTag(tag);
}

void Balloon::SetOwner(class Actor* owner) 
{
	mOwner = owner;
}


void Balloon::UpdateActor()
{
	if (Actor::GetPos().x > 1500 || Actor::GetPos().y < 0)
	{
		Actor::SetState(EDead);
	}

	if(mOwner)
	{
		//Ownerがプレイヤーの場合
		if (mOwner->GetTag() == 1) 
		{
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
		//風船が手元から離れた場合、プレイヤーのP_Liftを０にする。でないと、風船が手元を離れても消滅するまでプレイヤーは浮かんでしまう。
		if (mOwner->GetTag() != 1) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Ownerが敵の場合
		if (mOwner->GetTag() >= 1000 || mOwner->GetTag() <= 9999)
		{
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
		Balloon::mPos = mOwner->GetPos();
		Balloon::mPos.y -= mLift;
		mOwner->Actor::SetPos(Balloon::mPos.x, Balloon::mPos.y);
	}
	//Owner不在でBalloonがリリースされた場合（プレイヤもしくはObstacleに属していないフリーな状態）
	else if(!mOwner)
	{
		mPos = Actor::GetPos();
		mPos.x += 20.0f;
		mPos.y -= 20.0f;
		Actor::SetPos(mPos.x, mPos.y);
		//風船が直接敵に当たった場合（場合分けしない場合、Obstacleの当たり判定と２重に判定されエラーとなる。
		for (auto enemy : GetGame()->GetEnemies())
		{
			if (HitCheckBC(Actor::GetPos(), 100, enemy->GetPos(), 100))
			{
				enemy->Damage(mDamage);//ヒットした対象にBalloonに設定したダメージを与える
				//Actor::SetState(EDead);//Balloonがヒットしたら消滅する。
			};
		}
	}
}