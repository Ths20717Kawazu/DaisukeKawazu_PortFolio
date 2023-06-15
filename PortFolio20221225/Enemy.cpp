#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

Enemy::Enemy(Game* game, enum Actor::Tag tagID):Actor(game, tagID)
{
	mHP = 100;
	mEscore = 200;
	SetVel(2.0f, 0.0f);
	animate = true;
	auto SC = new SpriteComponent(this, 300);
	auto CC = new CollisionComponent(this);
	auto AC = new AnimationComponent(this, 300);
	//**********************Enemyの各State毎に画像配列を初期化************************//
	AddImage(LoadTexture((char*)"images/gorem.png"), Enemy::IDLE);
	Actor::AnimImages = Enemy::GetAnimImages(Enemy::GetState());
	AddAnimOrders(0, IDLE);
	Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//基底クラスの画像順序配列を初期化する。
	GetGame()->AddEnemy(this);
	//Gridへの登録
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);

}

Enemy::~Enemy(){
	GetGame()->RemoveEnemy(this);
	
}

void Enemy::UpdateActor() 
{		

	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);

	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//現在のグリッドから削除
		mMygrid = newMygrid;//新たなグリッドを代入
		mMygrid->addMembersIngrid(this);//更新されたグリッドに自らを追加
	}




	D3DXVECTOR2 futurePos;
	D3DXVECTOR2 curPos;
	D3DXVECTOR2 lastPos;

	curPos = Actor::GetPos();

	//将来座標
	futurePos.x = curPos.x + mVel.x;
	mVel.y += Actor::mGravity;
	futurePos.y = curPos.y + mVel.y + ( getHeight() / 2 );//Enemy画像の丁度下端でブロックとの衝突判定

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
			if (HitCheckBLK(futurePos, actor, this) == true)
			{
				mVel.y = 0.0f;;
			}
		}
	}

	//***************************************************************************************************************************//
	//プレイヤの速度を取得してエネミーの移動に反映
	//if()
	//=======================================//
		D3DXVECTOR2 Pvel;
		if (GetGame()->GetPlayer()->GetState() == Actor::EActive) 
		{
			Pvel = GetGame()->GetPlayer()->getVel();
			//=======================================//

			//エネミーの移動速度
			//====================//
			mActor.pos = Actor::GetPos();
			mActor.pos.x += mVel.x;
			mActor.pos.y += mVel.y;
			//====================//

			//エネミーの移動に上で取得したプレイヤの移動速度を反映
			//====================//
			mActor.pos -= Pvel;
			//====================//
		}
		//上でエネミーに反映すべき移動速度を処理して最終的に反映
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
	//***************************************************************************************************************************//


	/*if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50)) 
	{
		GetGame()->GetPlayer()->Damage(100.0f);;
	};*/

}

void Enemy::Damage(int damage) 
{
	int score;
	mHP -= damage;

	if (mHP <= 0)
	{
		
		Actor::SetState(EDead);
		
		score = GetGame()->GetPlayer()->GetScore();
		score += GetEScore();
		GetGame()->GetPlayer()->SetScore(score);


	}

}


void Enemy::AddImage(int img, Enemy::EnemyState state)
{
	switch (state)
	{
	case Enemy::IDLE:
		mIdleImages.emplace_back(img);
		break;
	//case Enemy::WALK:
	//	mWalkImages.emplace_back();
	//	break;
	}
};

void Enemy::AddAnimOrders(int order, Enemy::EnemyState state)
{
	switch (state)
	{
	case Enemy::IDLE:
		animIdleOrders.emplace_back(order);
		break;
	/*case Enemy::WALK:
		mWalkImages.emplace_back();
		break;*/
	}
};

std::vector<int> Enemy::GetAnimImages(Enemy::EnemyState state)
{
	switch (state)
	{
	case Enemy::IDLE:
		return mIdleImages;
		break;
	case Enemy::WALK:
		return mWalkImages;
		break;
	}
}

std::vector<int> Enemy::GetAnimOrders(Enemy::EnemyState state)
{
	switch (state)
	{
	case Enemy::IDLE:
		return animIdleOrders;
		break;
	}
}
