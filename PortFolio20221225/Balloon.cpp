#include "Balloon.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "texture.h"
#include "Enemy.h"
#include "game.h"

Balloon::Balloon(Game* game):Actor(game)
{
	auto SC = new SpriteComponent(this);
	//auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/balloon.png"));
	mtag = 100.0f;
}

void Balloon::UpdateActor() 
{
	if (GetGame()->GetPlayer()->GetHasballoon())
	{
		float posx;
		float posy;
		posx = GetGame()->GetPlayer()->GetPos().x;
		posy = GetGame()->GetPlayer()->GetPos().y;
		posx += 100.0f;
		posy -= 10.0f;
		Actor::SetPos(posx, posy);
	}


	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(Balloon::GetPos(), 200, enemy->GetPos(), 200))
		{
			Actor::SetState(EDead);
			//hit = true;

		};

	}


}