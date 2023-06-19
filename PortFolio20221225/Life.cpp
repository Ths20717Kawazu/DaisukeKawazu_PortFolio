#include "game.h"
#include "CameraComponent.h"
#include "Life.h"
#include "SpriteComponent.h"
#include "texture.h"

Life::Life(Game* game, Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot, int num) : Actor(game, tag)
{
	mNum = num;
	animate = false;
	auto SC = new SpriteComponent(this, 750);
	SC->SetTextureID(LoadTexture((char*)"images/Life.png"));
	SetACTOR(posX, posY, BoxH, BoxW, UvU, UvV, VH, VW, Rot);
	GetGame()->AddLife(this);
}

Life::~Life()
{
	GetGame()->RemoveLife(this);

};

void Life::UpdateActor()
{
	
	SetPos(GetGame()->GetCamera()->GetCameraPos().x + 300.0f + mNum * 50, GetGame()->GetCamera()->GetCameraPos().y + 950.0f);
}