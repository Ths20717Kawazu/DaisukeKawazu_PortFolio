#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, int tagID): Actor(game, tagID),
mLift(50.0f),
mDamage(20)
{
	auto SC = new SpriteComponent(this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	SetOwner(GetGame()->GetPlayer());
	int tag = Actor::GetTag();
	//tag++;
	Actor::SetTag(tag);
	GetGame()->GetPlayer()->SetLift(-70.0f);
	GetGame()->AddBalloon(this);

}

Balloon::~Balloon() {
	
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
		//Owner‚ªƒvƒŒƒCƒ„[‚Ìê‡
		if (mOwner->GetTag() == 1) 
		{
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
		//Owner‚ª“G‚Ìê‡
		if (mOwner->GetTag() >= 1000 || mOwner->GetTag() <= 9999)
		{
			mPos = mOwner->GetPos();
			mPos.x += 100.0f;
			mPos.y -= 10.0f;
			Actor::SetPos(mPos.x, mPos.y);
		}
	}
	else 
	{
		mPos = Actor::GetPos();
		mPos.x += 100.0f;
		mPos.y -= 10.0f;
		Actor::SetPos(mPos.x, mPos.y);
	
	}

	//for (auto enemy : GetGame()->GetEnemies()) 
	//{
	//	if (HitCheckBC(Balloon::GetPos(), 100, enemy->GetPos(), 100))
	//	{
	//		enemy->Damage(mDamage);
	//		Actor::SetState(EDead);
	//		//hit = true;
	//	};
	//}
}