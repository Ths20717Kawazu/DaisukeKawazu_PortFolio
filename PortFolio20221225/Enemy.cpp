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
}

Enemy::~Enemy(){
	GetGame()->RemoveEnemy(this);
	
}

void Enemy::UpdateActor() 
{		
	//エネミーのState
	enum Enemy::EnemyState curstate = Enemy::GetState();
	if (curstate != Enemy::GetState())//Stateが切り替わったのなら、新たな画像配列を基底クラスが有する画像配列等に入力する。
	{
		Actor::AnimImages = GetAnimImages(Enemy::GetState());//基底クラスの画像配列にState毎の画像を入力し、AnimationComponentで呼び出す。
		Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//基底クラスの画像順番配列にState毎の配列を入力し、AnimationComponent。
	}

	//***************************************************************************************************************************//
	//プレイヤの速度を取得してエネミーの移動に反映
	//=======================================//
		D3DXVECTOR2 Pvel;
		Pvel = GetGame()->GetPlayer()->getVel();
		//=======================================//

		//エネミーの移動速度
		//====================//
		mActor.pos = Actor::GetPos();
		mActor.pos.x += 5.0f;
		//====================//

		//エネミーの移動に上で取得したプレイヤの移動速度を反映
		//====================//
		mActor.pos -= Pvel;
		//====================//

		//上でエネミーに反映すべき移動速度を処理して最終的に反映
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
	//***************************************************************************************************************************//


	if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50)) 
	{
		GetGame()->GetPlayer()->Damage(1.0f);;
	};

}

void Enemy::Damage(int damage) 
{
	mHP -= damage;

	if (mHP <= 0)
	{
		Actor::SetState(EDead);
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
