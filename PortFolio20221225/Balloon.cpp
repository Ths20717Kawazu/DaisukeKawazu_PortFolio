#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, enum Actor::Tag tag): Actor(game, tag),
mLift(5.0f),
mDamage(100)
{
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	SetOwner(GetGame()->GetPlayer());
	animate = false;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(-2.03f);//�v���C���ɕ��͂�^����
	GetGame()->AddBalloon(this);
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
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
		//���D���茳���痣�ꂽ�ꍇ�A�v���C���[��P_Lift���O�ɂ���B�łȂ��ƁA���D���茳�𗣂�Ă����ł���܂Ńv���C���[�͕�����ł��܂��B
		if (mOwner->GetTag() != 1) 
		{
			GetGame()->GetPlayer()->SetLift(0.0f);
		}
		//Owner���G�̏ꍇ
		if (mOwner->GetTag() >= 1000 || mOwner->GetTag() <= 9999)
		{
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
		Balloon::mPos = mOwner->GetPos();
		Balloon::mPos.y -= mLift;
		mOwner->Actor::SetPos(Balloon::mPos.x, Balloon::mPos.y);
	}
	//Owner�s�݂�Balloon�������[�X���ꂽ�ꍇ�i�v���C����������Obstacle�ɑ����Ă��Ȃ��t���[�ȏ�ԁj
	else if(!mOwner)
	{
		mPos = Actor::GetPos();
		mPos.x += 20.0f;
		mPos.y -= 20.0f;
		Actor::SetPos(mPos.x, mPos.y);
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