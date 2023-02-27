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
	mPos.x += 2.0f;
	Actor::SetPos(mPos.x, mPos.y);

	count++;
	if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50)) {
		GetGame()->GetPlayer()->Damage(1.0f);
		//Actor::SetState(EDead);
		hit = true;
	
	};

	////現在のプレイヤの位置情報	
	//D3DXVECTOR2 tempPos;
	//D3DXVECTOR2 curPos;
	//D3DXVECTOR2 lastPos;
	////mGravity.y += 0.1f;
	//curPos = Actor::GetPos();

	////移動方向をベクトル正規化
	//D3DXVec2Normalize(&mDir, &mDir);

	//mVel = mDir * mSpeed;
	//mVel.y += mGravity;
	////mVel.y += GetLift();
	////mVel.y += -100.0f;

	//mVel.y += mJumpVel;
	////mVel.y -= mJumpVel - 5.0f;
	//mJumpVel += mGravity;

	////入力を受け付けた場合の将来座標
	//tempPos.x = curPos.x + mVel.x;
	//tempPos.y = curPos.y + mVel.y;
	////tempPos.y = curPos.y + mVel.y + mGravity.y;

	////画面外への移動を禁止
	//if (tempPos.x <= 0 || tempPos.x >= 1500)
	//{
	//	mVel.x = 0.0;
	//}

	//for (auto block : GetGame()->GetBlocks())
	//{
	//	//将来座標がブロックと衝突することが分かる場合（現段階では上からの接触のみ対応となっている）
	//	if (HitCheckBLK(tempPos, block, this) == true)
	//	{
	//		//lastPos = getPos();
	//		//mVel.x = 0.0;　
	//		mVel.y = 0.0f;
	//		mJumpVel = 0.0f;
	//		//isInAir = false;
	//		//setSpeed(10.0f);
	//	}

	//}
	////for (auto enemy : GetGame()->GetEnemies())
	////{
	////	//HitCheckBC(tempPos, 10, enemy->GetPos(), 10)の第２及び第３引数の値が大きすぎると、エネミー側の当たり判定が実行されない
	////	//つまり、エネミー側にあたる前にストップしてしまう。そもそも、Posの値をtempPosにする必用があるのか？
	////	if (HitCheckBC(tempPos, 10, enemy->GetPos(), 10)) {
	////		mVel.x = 0.0;
	////		mVel.y = 0.0;
	////		//Actor::SetState(EDead);
	////	}
	//}
	//mDir.y = 0.0f;
	//mDir.x = 0.0f;
	//mPos.x += mVel.x;
	//mPos.y += mVel.y;
	//SetPos(mPos.x, mPos.y);
}

void Enemy::Damage(int damage) 
{
	mHP -= damage;
	if (mHP <= 0) {
		Actor::SetState(EDead);
	}

}