#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, enum Actor::Tag tag): Actor(game, tag),
mDamage(100)
{
	auto SC = new SpriteComponent(this, 500);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	SetOwner(GetGame()->GetPlayer());//最初のオーナーをプレイヤーに設定
	animate = false;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(mLift);//プレイヤに浮力を与える
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
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);

	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//現在のグリッドから削除
		mMygrid = newMygrid;//新たなグリッドを代入
		mMygrid->addMembersIngrid(this);//更新されたグリッドに自らを追加
	}


	if (Actor::GetPos().x > 5000 || Actor::GetPos().x < -100 || Actor::GetPos().y < -500 || Actor::GetPos().y > 2000)
	{
		Actor::SetState(EDead);
	}

	if(mOwner)
	{
		//Ownerがプレイヤーの場合
		if (mOwner->GetTag() == Actor::Player) 
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 50.0f;
			mActor.pos.y -= 100.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//風船が手元から離れた場合、プレイヤーのP_Liftを０にする。でないと、風船が手元を離れても消滅するまでプレイヤーは浮かんでしまう。
		if (mOwner->GetTag() != Actor::Player) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Ownerが敵の場合
		if(mOwner->GetTag() == Actor::Enemy)
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 100.0f;
			mActor.pos.y -= 100.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//mOwnerがMonoの場合
		if (mOwner->GetTag() == Actor::Mono)
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 50.0f;
			mActor.pos.y -= 200.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}


	}
	//Owner不在でBalloonがリリースされた場合（プレイヤもしくはMonoに属していないフリーな状態）
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
		mSpeed -= Actor::mGravity;
		mActor.pos.y -= mSpeed;

		//====================//
		//上で風船に反映すべき移動速度を処理して最終的に反映
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
		//***************************************************************************************************************************//
		//風船が直接敵に当たった場合（場合分けしない場合、Monoの当たり判定と２重に判定されエラーとなる。
		for (auto actor : mMygrid->GetGridMembers()) 
		{
			if (actor->GetTag() == Actor::Mono) 
			{
				if (HitCheckBC(Actor::GetPos(), 100, actor->Actor::GetPos(), 100))
				{
					SetOwner(actor);
					actor->Actor::setLift(mLift);
					//if (GetKeyboardTrigger(DIK_RETURN))
					//{
					//	mPlayer->GetGame()->GetBalloon()->SetOwner(mPlayer->GetGame()->GetMono());
					//}
				}		

			}
			if (actor->GetTag() == Actor::Enemy)
			{
				if (HitCheckBC(Actor::GetPos(), 100, actor->GetPos(), 100))
				{
					actor->Damage(mDamage);//ヒットした対象にBalloonに設定したダメージを与える
					//Actor::SetState(EDead);//Balloonがヒットしたら消滅する。
				};
			}
		}
	}
}