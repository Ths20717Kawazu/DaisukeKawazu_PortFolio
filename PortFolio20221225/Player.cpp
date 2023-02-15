#include "Game.h"
#include "Player.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"


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
	:Actor(game), mHP(100), mGame(game), mSpeed(10.0f), playerPos(100.0f, 100.0f)
{
	//mState = ESTAND;
	//setState(ESTAND);
	//下記コンポネントがnewされると、各コンポーネント配下ではPlayer（Owner）を呼び出せる
	auto SC = new SpriteComponent(this, this);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this, this);
	SC->SetTextureID(LoadTexture((char*)"images/Player.png"));
	
	GetGame()->addPlayer(this);
}

Player::~Player() {};


void Player::DrawPlayer(void)
{
	//キャラクターの描画
	//テクスチャ識別子のセット

}

void Player::UpdateActor(void) 
{
	D3DXVECTOR2 lastpos;
	lastpos = GetPos();
	

	//Gameクラスが管理する全てのアクターを取り出し、プレイヤーと衝突判定を実施する。
	for (auto enemy : GetGame()->GetActors()) 
	{
		if (HitCheckBC(GetPos(), 50, enemy->GetPos(), 50)) {
			//Damage();

		}

		//SetPos(GetACTOR().pos.x, GetACTOR().pos.y);

	}
	//HitCheckBC()

	////ウィンドウの外に出たらDead
	//VECTOR2 pos = GetPosition();
	//if (pos.x < -50 || pos.x > width + 50)
	//{
	//	SetState(EDead);
	//}
	//else
	//{
	//	//Shipとの衝突判定
	//	if (auto ship = GetGame()->GetShip())
	//	{
	//		if (Intersect(mRect, ship->GetRect()))
	//		{
	//			SetState(EDead);
	//			ship->Damage();
	//		}
	//	}
	//}

}

void Player::Damage() 
{
	mHP -= 5;
	if (mHP <= 0) {
		mState = Actor::EDead;
	}
};
