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

	////���݂̃v���C���̈ʒu���	
	//D3DXVECTOR2 tempPos;
	//D3DXVECTOR2 curPos;
	//D3DXVECTOR2 lastPos;
	////mGravity.y += 0.1f;
	//curPos = Actor::GetPos();

	////�ړ��������x�N�g�����K��
	//D3DXVec2Normalize(&mDir, &mDir);

	//mVel = mDir * mSpeed;
	//mVel.y += mGravity;
	////mVel.y += GetLift();
	////mVel.y += -100.0f;

	//mVel.y += mJumpVel;
	////mVel.y -= mJumpVel - 5.0f;
	//mJumpVel += mGravity;

	////���͂��󂯕t�����ꍇ�̏������W
	//tempPos.x = curPos.x + mVel.x;
	//tempPos.y = curPos.y + mVel.y;
	////tempPos.y = curPos.y + mVel.y + mGravity.y;

	////��ʊO�ւ̈ړ����֎~
	//if (tempPos.x <= 0 || tempPos.x >= 1500)
	//{
	//	mVel.x = 0.0;
	//}

	//for (auto block : GetGame()->GetBlocks())
	//{
	//	//�������W���u���b�N�ƏՓ˂��邱�Ƃ�������ꍇ�i���i�K�ł͏ォ��̐ڐG�̂ݑΉ��ƂȂ��Ă���j
	//	if (HitCheckBLK(tempPos, block, this) == true)
	//	{
	//		//lastPos = getPos();
	//		//mVel.x = 0.0;�@
	//		mVel.y = 0.0f;
	//		mJumpVel = 0.0f;
	//		//isInAir = false;
	//		//setSpeed(10.0f);
	//	}

	//}
	////for (auto enemy : GetGame()->GetEnemies())
	////{
	////	//HitCheckBC(tempPos, 10, enemy->GetPos(), 10)�̑�Q�y�ё�R�����̒l���傫������ƁA�G�l�~�[���̓����蔻�肪���s����Ȃ�
	////	//�܂�A�G�l�~�[���ɂ�����O�ɃX�g�b�v���Ă��܂��B���������APos�̒l��tempPos�ɂ���K�p������̂��H
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