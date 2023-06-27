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
	SetOwner(GetGame()->GetPlayer());//�ŏ��̃I�[�i�[���v���C���[�ɐݒ�
	animate = false;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(mLift);//�v���C���ɕ��͂�^����
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
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);

	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//���݂̃O���b�h����폜
		mMygrid = newMygrid;//�V���ȃO���b�h����
		mMygrid->addMembersIngrid(this);//�X�V���ꂽ�O���b�h�Ɏ����ǉ�
	}


	if (Actor::GetPos().x > 5000 || Actor::GetPos().x < -100 || Actor::GetPos().y < -500 || Actor::GetPos().y > 2000)
	{
		Actor::SetState(EDead);
	}

	if(mOwner)
	{
		//Owner���v���C���[�̏ꍇ
		if (mOwner->GetTag() == Actor::Player) 
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 50.0f;
			mActor.pos.y -= 100.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//���D���茳���痣�ꂽ�ꍇ�A�v���C���[��P_Lift���O�ɂ���B�łȂ��ƁA���D���茳�𗣂�Ă����ł���܂Ńv���C���[�͕�����ł��܂��B
		if (mOwner->GetTag() != Actor::Player) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Owner���G�̏ꍇ
		if(mOwner->GetTag() == Actor::Enemy)
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 100.0f;
			mActor.pos.y -= 100.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}
		//mOwner��Mono�̏ꍇ
		if (mOwner->GetTag() == Actor::Mono)
		{
			mActor.pos = mOwner->GetPos();
			mActor.pos.x += 50.0f;
			mActor.pos.y -= 200.0f;
			Actor::SetPos(mActor.pos.x, mActor.pos.y);
		}


	}
	//Owner�s�݂�Balloon�������[�X���ꂽ�ꍇ�i�v���C����������Mono�ɑ����Ă��Ȃ��t���[�ȏ�ԁj
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
		mSpeed -= Actor::mGravity;
		mActor.pos.y -= mSpeed;

		//====================//
		//��ŕ��D�ɔ��f���ׂ��ړ����x���������čŏI�I�ɔ��f
		Actor::SetPos(mActor.pos.x, mActor.pos.y);
		//***************************************************************************************************************************//
		//���D�����ړG�ɓ��������ꍇ�i�ꍇ�������Ȃ��ꍇ�AMono�̓����蔻��ƂQ�d�ɔ��肳��G���[�ƂȂ�B
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
					actor->Damage(mDamage);//�q�b�g�����Ώۂ�Balloon�ɐݒ肵���_���[�W��^����
					//Actor::SetState(EDead);//Balloon���q�b�g��������ł���B
				};
			}
		}
	}
}