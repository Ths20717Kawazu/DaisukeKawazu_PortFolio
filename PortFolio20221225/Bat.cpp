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
		mMygrid->removeMembersIngrid(this);//���݂̃O���b�h����폜
		mMygrid = newMygrid;//�V���ȃO���b�h����
		mMygrid->addMembersIngrid(this);//�X�V���ꂽ�O���b�h�Ɏ����ǉ�
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
	//�������W
	futurePos.x = curPos.x + mVel.x;
	futurePos.y = curPos.y + mVel.y;




	//futurePos.y = curPos.y + mVel.y + ( getHeight() / 2 );//Enemy�摜�̒��x���[�Ńu���b�N�Ƃ̏Փ˔���
	//�G�l�~�[��State
	enum Enemy::EnemyState curstate = Enemy::GetState();
	if (curstate != Enemy::GetState())//State���؂�ւ�����̂Ȃ�A�V���ȉ摜�z������N���X���L����摜�z�񓙂ɓ��͂���B
	{
		Actor::AnimImages = GetAnimImages(Enemy::GetState());//���N���X�̉摜�z���State���̉摜����͂��AAnimationComponent�ŌĂяo���B
		Actor::AnimOrders = GetAnimOrders(Enemy::GetState());//���N���X�̉摜���Ԕz���State���̔z�����͂��AAnimationComponent�B
	}

	//�u���b�N�Ƃ̏Փ˔���
	for (auto actor : mMygrid->GetGridMembers())
	{
		if (actor->GetTag() == Actor::Block)
		{
			HitCheckBLK(&futurePos, actor, this);
		}
	}

	//***************************************************************************************************************************//

	//=======================================//

			//�G�l�~�[�̈ړ����x
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
