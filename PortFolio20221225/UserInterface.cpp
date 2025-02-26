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
	
	//カメラの位置に座標が設定されていることから、Ｘ座標及びＹ座標に画面の半分を加算する必用がある
	SetPos(GetGame()->GetCamera()->GetCameraPos().x + 950, GetGame()->GetCamera()->GetCameraPos().y + 800 );
	
}