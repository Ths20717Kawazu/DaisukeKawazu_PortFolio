#include "UserInterface.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"

UserInterface::UserInterface(Game* game, Actor::Tag tag) :Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 700);
	SC->SetTextureID(LoadTexture((char*)"images/UI_Shita.png"));

}

UserInterface::~UserInterface() {};

void UserInterface::UpdateActor()
{
	//D3DXVECTOR2 Pvel;
	//if ( GetGame()->GetPlayer()->GetState() == Actor::EActive)
	//{
	//	Pvel = GetGame()->GetPlayer()->getVel();
	//	mActor.pos += Pvel;
	//	//mPos += {mVel.x, mVel.y};
	//}
	//SetPos(mActor.pos.x, mActor.pos.y);
	
	//ƒJƒƒ‰‚ÌˆÊ’u‚ÉÀ•W‚ªÝ’è‚³‚ê‚Ä‚¢‚é‚±‚Æ‚©‚çA‚wÀ•W‹y‚Ñ‚xÀ•W‚É‰æ–Ê‚Ì”¼•ª‚ð‰ÁŽZ‚·‚é•K—p‚ª‚ ‚é
	SetPos(GetGame()->GetCamera()->GetCameraPos().x + 950, GetGame()->GetCamera()->GetCameraPos().y + 800 );
	
}