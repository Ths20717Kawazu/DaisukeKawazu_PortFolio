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
	GetGame()->GetPlayer()->SetLift(-2.03f);//�v���C���ɕ��͂�^����
	GetGame()->AddBalloon(this);

	//Grid�ւ̓o�^
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
		//Owner���v���C���[�̏ꍇ
		if (mOwner->GetTag() == 1) 
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 100.0f;
			mActor.pos.y -= 10.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//���D���茳���痣�ꂽ�ꍇ�A�v���C���[��P_Lift���O�ɂ���B�łȂ��ƁA���D���茳�𗣂�Ă����ł���܂Ńv���C���[�͕�����ł��܂��B
		if (mOwner->GetTag() != Actor::Player) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Owner���G�̏ꍇ
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
	//Owner�s�݂�Balloon�������[�X���ꂽ�ꍇ�i�v���C����������Obstacle�ɑ����Ă��Ȃ��t���[�ȏ�ԁj
	else if(!mOwner)
	{

	//***************************************************************************************************************************//
	//�v���C���̑��x���擾���ĕ��D�̈ړ��ɔ��f
	//=======================================//
		D3DXVECTOR2 Pvel;
		Pvel = GetGame()->GetPlayer()->getVel();
		//=======================================//

		//���D�̈ړ����x
		//====================//
		mActor.pos = Actor::GetPos();
		mActor.pos.x += 5.0f;
		mActor.pos.y -= 5.0f;
		//====================//

		//���D�̈ړ��ɏ�Ŏ擾�����v���C���̈ړ����x�𔽉f
		//====================//
		mActor.pos -= Pvel;
		//====================//

		//��ŕ��D�ɔ��f���ׂ��ړ����x���������čŏI�I�ɔ��f
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
		//***************************************************************************************************************************//


		//���D�����ړG�ɓ��������ꍇ�i�ꍇ�������Ȃ��ꍇ�AObstacle�̓����蔻��ƂQ�d�ɔ��肳��G���[�ƂȂ�B
		for (auto enemy : GetGame()->GetEnemies())
		{
			if (HitCheckBC(Actor::GetPos(), 100, enemy->GetPos(), 100))
			{
				enemy->Damage(mDamage);//�q�b�g�����Ώۂ�Balloon�ɐݒ肵���_���[�W��^����
				//Actor::SetState(EDead);//Balloon���q�b�g��������ł���B
			};
		}
	}
}