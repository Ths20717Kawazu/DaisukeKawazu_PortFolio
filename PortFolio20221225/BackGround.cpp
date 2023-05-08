#include "BackGround.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"


BackGround::BackGround(Game* game, enum Actor::Tag tag):Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/mori.jpg"));
}

BackGround::~BackGround() {};

void BackGround::UpdateActor() 
{
//初期化の際に、Playerのコンストラクタが呼び出される前にBackgroundのコンストラクタが呼び出されるため
//GetPosはNULLであるためエラーが発生する。よって、描画順序とコンストラクタは別にする必用がある。
  mPlayerPos = GetPPos();
};