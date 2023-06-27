#include "Bat.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

Bat::Bat(Game* game, enum Actor::Tag tagID, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot) : Enemy( game,  tagID,  posX,  posY,  BoxH,  BoxW,  UvU,  UvV,  VH,  VW,  Rot)
{
	SetVel(2.0f, 0.0f);
	animate = true;
	auto SC = new SpriteComponent(this, 300);
	auto CC = new CollisionComponent(this);
	auto AC = new AnimationComponent(this, 300);
	AddImage(LoadTexture((char*)"images/gorem.png"), Enemy::IDLE);

}

Bat::~Bat() {
	GetGame()->RemoveEnemy(this);

}

void Bat::UpdateActor()
{
	Actor::GetPos();
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	D3DXVec2Normalize(&mDir, &mDir);


	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//現在のグリッドから削除
		mMygrid = newMygrid;//新たなグリッドを代入
		mMygrid->addMembersIngrid(this);//更新されたグリッドに自らを追加
	}

	for (auto actor : mMygrid->GetGridMembers())
	{
		//=========================================//
		if (actor->GetTag() == Actor::Block)
		{
			if (!actor->GetPos().y == (Actor::GetPos().y + ((EnemyHeight / 2) + (Actor::BlockHeight / 2))))
			{
				isInAir = true;
				break;
			}
			else
			{
				isInAir = false;
			}
		}
	}

	if (isInAir)
	{
		setGravity(1.0f);
	}
	else
	{
		setGravity(0.0f);
	}



	D3DXVECTOR2 futurePos;
	D3DXVECTOR2 curPos;
	D3DXVECTOR2 lastPos;




	curPos = Actor::GetPos();
	mVel.y += Actor::mGravity;
	if (mVel.y >= 10.0f) { mVel.y = 10.0f; }
	mVel.x = mDir.x * mSpeed;
	//将来座標
	futurePos.x = curPos.x + mVel.x;
	futurePos.y = curPos.y + mVel.y;




	//futurePos.y = curPos.y + mVel.y + ( getHeight() / 2 );//Enemy画像の丁度下端でブロックとの衝突判定
	//エネミーのState
	enum Enemy::EnemyState curstate = Enemy::GetState();
	if (curstate != Enemy::GetState())//Stateが切り替わったのなら、新たな画像配列を基底クラスが有する画像配列等に入力する。
	{
		Actor::AnimImages = GetAnimImages(Enemy::GetState());//基底クラスの画像配列にState毎の画像を入力し、AnimationComponentで呼び出す。
		Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//基底クラスの画像順番配列にState毎の配列を入力し、AnimationComponent。
	}

	//ブロックとの衝突判定
	for (auto actor : mMygrid->GetGridMembers())
	{
		if (actor->GetTag() == Actor::Block)
		{
			HitCheckBLK(&futurePos, actor, this);
		}
	}

	//***************************************************************************************************************************//

	//=======================================//

			//エネミーの移動速度
			//====================//
	mActor.pos = Actor::GetPos();
	mActor.pos.x = futurePos.x;
	mActor.pos.y = futurePos.y;

	//====================//

	Actor::SetPos(mActor.pos.x, mActor.pos.y);
	//***************************************************************************************************************************//

	if (futurePos.y < 0 || futurePos.y >= 2000)
	{
		Actor::SetState(EDead);
	}
	if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50))
	{
		GetGame()->GetPlayer()->Damage(100.0f);;
	};


}
