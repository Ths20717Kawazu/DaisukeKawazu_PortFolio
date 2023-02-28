#include "Obstacle.h"
#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"



Obstacle::Obstacle(Game* game, int tagID) :Actor(game, tagID),
mDamage(100)
{
	mHP = 100;
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/obstacle.png"));
	GetGame()->AddObstacle(this);
}

Obstacle::~Obstacle() {


}

void Obstacle::UpdateActor() 
{
	//���݂̃v���C���̈ʒu���	
	//D3DXVECTOR2 tempPos;
	//D3DXVECTOR2 curPos;
	//D3DXVECTOR2 lastPos;
	////mGravity.y += 0.1f;
	//curPos = Actor::GetPos();

	//mPos = Actor::GetPos();
	//mPos.y -= mGravity;
	//Actor::SetPos(mPos.x, mPos.y);


	////���͂��󂯕t�����ꍇ�̏������W
	//tempPos.y = curPos.y + mGravity;
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
	//		isInAir = false;
	//		setSpeed(10.0f);
	//	}




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
