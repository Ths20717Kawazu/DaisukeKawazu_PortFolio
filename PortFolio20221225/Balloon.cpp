#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, enum Actor::Tag tag): Actor(game, tag),
mLift(5.0f),
mDamage(100)
{
	auto SC = new SpriteComponent(this, 500);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	SetOwner(GetGame()->GetPlayer());
	animate = false;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(-2.03f);//プレイヤに浮力を与える
	GetGame()->AddBalloon(this);

	//Gridへの登録
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);

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
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 100.0f;
			mActor.pos.y -= 10.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//風船が手元から離れた場合、プレイヤーのP_Liftを０にする。でないと、風船が手元を離れても消滅するまでプレイヤーは浮かんでしまう。
		if (mOwner->GetTag() != Actor::Player) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Ownerが敵の場合
		//if (mOwner->GetTag() >= 1000 || mOwner->GetTag() <= 9999)
		if(mOwner->GetTag() == Actor::Enemy)
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 100.0f;
			mActor.pos.y -= 10.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		Balloon::mActor.pos = mOwner->GetPos();
		Balloon::mActor.pos.y -= mLift;
		mOwner->Actor::SetPos(Balloon::mActor.pos.x, Balloon::mActor.pos.y);
	}
	//Owner不在でBalloonがリリースされた場合（プレイヤもしくはObstacleに属していないフリーな状態）
	else if(!mOwner)
	{

	//***************************************************************************************************************************//
	//プレイヤの速度を取得して風船の移動に反映
	//=======================================//
		D3DXVECTOR2 Pvel;
		Pvel = GetGame()->GetPlayer()->getVel();
		//=======================================//

		//風船の移動速度
		//====================//
		mActor.pos = Actor::GetPos();
		mActor.pos.x += 5.0f;
		mActor.pos.y -= 5.0f;
		//====================//

		//風船の移動に上で取得したプレイヤの移動速度を反映
		//====================//
		mActor.pos -= Pvel;
		//====================//

		//上で風船に反映すべき移動速度を処理して最終的に反映
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
		//***************************************************************************************************************************//


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