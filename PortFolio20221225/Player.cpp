#include "Player.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"

//定数宣言
#define BOX_WIDTH	(100.0f) //箱の幅
#define BOX_HEIGHT	(100.0f) //箱の高さ

//static PLAYER g_Player;
static int g_TextureChara;
static int g_AnimePtn;
static int g_AnimeWait;
static int g_Muki;



//データをあらかじめテーブル化する
static float g_AnimeUV[4] =
{
	0.0f,
	0.333333f,
	0.666666f,
	0.333333f,
};

Player::Player(Game* game) 
	:Actor(game)
{
	//下記コンポネントがnewされると、各コンポーネント配下ではPlayer（Owner）を呼び出せる
	auto SC = new SpriteComponent(this);
	auto IC = new InputComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/enemy.png"));
	
}

Player::~Player() {};


void Player::DrawPlayer(void)
{
	//キャラクターの描画
	//テクスチャ識別子のセット

}
