#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Enemy.h"
#include "Balloon.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"

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

Player::Player(Game* game, enum Actor::Tag tag)
	:Actor(game, tag), 
	mGame(game), 
	mSpeed(10.0f), 
	PlayerHeight(300), 
	PlayerWidth(300), 
	mGravity(2.0f),
	P_mLift(0.0f),
	mJumpVel(0.0f)
{
	//親クラスであるActorのProtectedのメンバ変数の初期化は↓のように実施する必用がある。
	mHP = 100;
	mPos = { 100.0f, 500.0f };
	animate = true;

	//下記コンポネントがnewされると、各コンポーネント配下ではPlayer（Owner）を呼び出せる
	//auto SC = new SpriteComponent(this, this);
	auto SC = new SpriteComponent(this);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	//auto AC = new AnimationComponent(this, this);//Playerと他のアニメーションするキャラを別にしていたが、その必用性はない
	auto AC = new AnimationComponent(this);

	//==================各State毎に使用する画像をそれぞれ配列にいれていく======================//

	//プレイヤがEIDLE状態の画像
    AddImage(LoadTexture((char*)"images/Player.png"),IDLE);
	AddImage(LoadTexture((char*)"images/Player_2.png"), IDLE);
	AddImage(LoadTexture((char*)"images/Player_3.png"), IDLE);
	Actor::AnimImages = GetAnimImages(Player::GetState());//基底クラスの画像配列を初期化する。

	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(1, IDLE);
	AddAnimOrders(2, IDLE);
	AddAnimOrders(2, IDLE);
	Actor::AnimOrders = GetAnimOrders(Player::GetState());//基底クラスの画像順序配列を初期化する。

	//AddAnimOrders(1, IDLE);
	//AddAnimOrders(2, IDLE);
	//AddAnimOrders(2, IDLE);


	//プレイヤがEWALK状態の画像
	//AddImage(LoadTexture((char*)"images/Player_Walk_1.png"), WALK);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EWALK);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EWALK);

	//プレイヤがERUN状態の画像
	//AC->AddImage(LoadTexture((char*)"images/Player.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EIDLE);

	////プレイヤがEJUMP状態の画像
	//AC->AddImage(LoadTexture((char*)"images/Player.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EIDLE);

	////プレイヤがEFALL状態の画像
	//AC->AddImage(LoadTexture((char*)"images/Player.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EIDLE);

	GetGame()->AddPlayer(this);
}

Player::~Player() 
{

};




void Player::UpdateActor(void) 
{
		//プレイヤのState
	enum Player::PlayerState curstate = Player::GetState();
	if (curstate != Player::GetState())//Stateが切り替わった場合
	{
	   Actor::AnimImages = GetAnimImages(Player::GetState());//基盤クラスの画像配列にState毎の画像を入力し、AnimationComponent。
	   Actor::AnimOrders = GetAnimOrders(Player::GetState());
	}

		//現在のプレイヤの位置情報	
		D3DXVECTOR2 tempPos;
		D3DXVECTOR2 curPos;
		D3DXVECTOR2 lastPos;
		curPos = getPos();
		if (!P_mLift == 0)
		{
			isInAir = true;
		}
		//移動方向をベクトル正規化
		D3DXVec2Normalize(&mDir, &mDir);
		mVel = mDir * mSpeed;
		mVel.y += mJumpVel;
		mJumpVel += mGravity + P_mLift;//重力により減衰


		//入力を受け付けた場合の将来座標
		tempPos.x = curPos.x + mVel.x;
		tempPos.y = curPos.y + mVel.y;
		//画面外への移動を禁止
		if (tempPos.x  <= 0 || tempPos.x >= 1500)
		{
			mVel.x = 0.0;
		}
		for (auto block : GetGame()->GetBlocks())
		{
			//将来座標がブロックと衝突することが分かる場合（現段階では上からの接触のみ対応となっている）
			if (HitCheckBLK(tempPos, block, this) == true)
			{
				mVel.y = 0.0f;
				mJumpVel = 0.0f;
				isInAir = false;
				setSpeed(10.0f);
			}
			else if (HitCheckBLK(getPos(), block, this) == true)
			{
				isInAir = false;
			}
			//else if (HitCheckBLK(getPos(), block, this) == false)
			else if (HitCheckBC(tempPos, 10, block->GetPos(), 10)) 
			{
				isInAir = true;
			}
			/*else if (HitCheckBC(tempPos, 100, block->GetPos(), 100) == false)
			{
				isInAir = true;
			}*/
		}
		//for (auto enemy : GetGame()->GetEnemies()) 
		//{	
		//	//HitCheckBC(tempPos, 10, enemy->GetPos(), 10)の第２及び第３引数の値が大きすぎると、エネミー側の当たり判定が実行されない
		//	//つまり、エネミー側にあたる前にストップしてしまう。そもそも、Posの値をtempPosにする必用があるのか？
		//	if (HitCheckBC(tempPos, 10, enemy->GetPos(), 10)) 
		//	{
		//		mVel = { 0.0, 0.0 };
		//	}
		//}
		mDir = { 0.0f, 0.0f };
		mPos += {mVel.x, mVel.y};
		SetPos(mPos.x, mPos.y);
}

void Player::Damage(int damage)
{
	mHP -= damage;
	if (mHP <= 0) {
		Actor::SetState(EDead);
	}
};

//引数のPlayerのStateに応じて
void Player::AddImage(int img, Player::PlayerState state) 
{
	switch (state) 
	{
		case Player::IDLE:
			mIdleImages.emplace_back(img);
			break;
	/*	case Player::WALK:
			mWalkImages.emplace_back();
			break;*/
	}
};
//AddImageまではOK　Vector配列には３つの要素がはいっているはず。


void Player::AddAnimOrders(int order, Player::PlayerState state)
{
	switch (state)
	{
	case Player::IDLE:
		animIdleOrders.emplace_back(order);
		break;
		/*	case Player::WALK:
				mWalkImages.emplace_back();
				break;*/
	}
};



//引数のPlayerのStateに応じて、画像配列を選択して返す
std::vector<int> Player::GetAnimImages(Player::PlayerState state)
{
	switch (state)
	{
	case Player::IDLE:
		return mIdleImages;
		break;

	//case Player::WALK:
	//	return mWalkImages;
	//	break;
	}
}

//引数のPlayerのStateに応じて、表示順序を選択して返す
std::vector<int> Player::GetAnimOrders(Player::PlayerState state)
{
	switch (state)
	{
	case Player::IDLE:
		return animIdleOrders;
		break;
	}
}

