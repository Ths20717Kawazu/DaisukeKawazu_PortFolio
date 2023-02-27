#include "Balloon.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"

Balloon::Balloon(Game* game, int tagID): Actor(game, tagID), mLift(50.0f)
{
	auto SC = new SpriteComponent(this);
	//auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	
	float posx;
	float posy;
	posx = GetGame()->GetPlayer()->GetPos().x;
	posy = GetGame()->GetPlayer()->GetPos().y;
	posx += 100.0f;
	posy -= 10.0f;
	Actor::SetPos(posx, posy);

	/*int tag = Actor::GetTag();
	tag++;
	Actor::SetTag(tag);*/
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
	float posx;
	float posy;
	/*if (mOwner->GetTag() == 1) 
	{
		posx = GetGame()->GetPlayer()->GetPos().x;
		posy = GetGame()->GetPlayer()->GetPos().y;
		posx += 100.0f;
		posy -= 10.0f;
		Actor::SetPos(posx, posy);
	}
	else 
	{*/
		posx = mOwner->GetPos().x;
		posy = mOwner->GetPos().y;
		posx += 100.0f;
		posy -= 10.0f;
		Actor::SetPos(posx, posy);
	//}


	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(Balloon::GetPos(), 200, enemy->GetPos(), 200))
		{
			Actor::SetState(EDead);
			//hit = true;

		};

	}


}