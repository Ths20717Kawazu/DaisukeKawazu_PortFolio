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
	SetVel(5.0f, 0.0f);
	animate = true;
	auto SC = new SpriteComponent(this, 300);
	auto CC = new CollisionComponent(this);
	auto AC = new AnimationComponent(this, 300);
	//**********************Enemy�̊eState���ɉ摜�z���������************************//
	AddImage(LoadTexture((char*)"images/gorem.png"), Enemy::IDLE);
	Actor::AnimImages = Enemy::GetAnimImages(Enemy::GetState());
	AddAnimOrders(0, IDLE);
	Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//���N���X�̉摜�����z�������������B
	GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){
	GetGame()->RemoveEnemy(this);
	
}

void Enemy::UpdateActor() 
{		

	D3DXVECTOR2 tempPos;
	D3DXVECTOR2 curPos;
	D3DXVECTOR2 lastPos;

	curPos = Actor::GetPos();

	//�������W
	tempPos.x = curPos.x + mVel.x;
	mVel.y += Actor::mGravity;
	tempPos.y = curPos.y + mVel.y + ( EnemyHeight / 2 );//Enemy�摜�̒��x���[�Ńu���b�N�Ƃ̏Փ˔���

	//�G�l�~�[��State
	enum Enemy::EnemyState curstate = Enemy::GetState();
	if (curstate != Enemy::GetState())//State���؂�ւ�����̂Ȃ�A�V���ȉ摜�z������N���X���L����摜�z�񓙂ɓ��͂���B
	{
		Actor::AnimImages = GetAnimImages(Enemy::GetState());//���N���X�̉摜�z���State���̉摜����͂��AAnimationComponent�ŌĂяo���B
		Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//���N���X�̉摜���Ԕz���State���̔z�����͂��AAnimationComponent�B
	}

	//�u���b�N�Ƃ̏Փ˔���
	for (auto block : GetGame()->GetBlocks())
	{
		//�������W���u���b�N�ƏՓ˂��邱�Ƃ�������ꍇ�i���i�K�ł͏ォ��̐ڐG�̂ݑΉ��ƂȂ��Ă���j
		for (auto block : GetGame()->GetBlocks())
		{
			//�������W���u���b�N�ƏՓ˂��邱�Ƃ�������ꍇ�i���i�K�ł͏ォ��̐ڐG�̂ݑΉ��ƂȂ��Ă���j
			if (HitCheckBLK(tempPos, block, this) == true)
			{
				mVel.y = 0.0f;
			}
		}
	}

	//***************************************************************************************************************************//
	//�v���C���̑��x���擾���ăG�l�~�[�̈ړ��ɔ��f
	//=======================================//
		D3DXVECTOR2 Pvel;
		Pvel = GetGame()->GetPlayer()->getVel();
		//=======================================//

		//�G�l�~�[�̈ړ����x
		//====================//
		mActor.pos = Actor::GetPos();
		mActor.pos.x += mVel.x;
		mActor.pos.y += mVel.y;
		//====================//

		//�G�l�~�[�̈ړ��ɏ�Ŏ擾�����v���C���̈ړ����x�𔽉f
		//====================//
		mActor.pos -= Pvel;
		//====================//

		//��ŃG�l�~�[�ɔ��f���ׂ��ړ����x���������čŏI�I�ɔ��f
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
