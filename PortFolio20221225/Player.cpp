#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Enemy.h"
#include "Life.h"
#include "Balloon.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "GameOver.h"
#include "Grid.h"
#include "CameraComponent.h"

//定数宣言
#define BOX_WIDTH	(100.0f) //箱の幅
#define BOX_HEIGHT	(100.0f) //箱の高さ
#define DISP_POS_X	(960.0f)	//プレイヤー表示座標X
#define DISP_POS_Y	(540.0f)	//プレイヤー表示座標Y
#define MAP_WIDTH_MAX	(2500.0f) //MAPの右限界
#define MAP_HEIGHT_MAX	(2000.0f) //MAPの高さ限界



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
	0.333333f
};

Player::Player(Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot)
	:Actor(game, tag),
	mGame(game),
	mSpeed(10.0f),
	//PlayerHeight(300),
	//PlayerWidth(300),
	mGravity(2.0f),
	P_mLift(0.0f),
	mJumpVel(0.0f),
	mRemainLives(5)
{
	//親クラスであるActorのProtectedのメンバ変数の初期化は↓のように実施する必用がある。
	mHP = 100;
	//mPos = { 100.0f, 200.0f };
	animate = true;
	SetACTOR(posX, posY, BoxH, BoxW, UvU, UvV, VH, VW, Rot);
	mPos = { posX, posY };
	
	//Gridへの登録
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);
	
	//下記コンポネントがnewされると、各コンポーネント配下ではPlayer（Owner）を呼び出せる
	//auto SC = new SpriteComponent(this, this);
	auto SC = new SpriteComponent(this, 600);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	//auto AC = new AnimationComponent(this, this);//Playerと他のアニメーションするキャラを別にしていたが、その必用性はない
	auto AC = new AnimationComponent(this, 600);

	//==================各State毎に使用する画像をそれぞれ配列にいれていく======================//

	//プレイヤがEIDLE状態の画像
    AddImage(LoadTexture((char*)"images/Player.png"),IDLE);
	AddImage(LoadTexture((char*)"images/Player_2.png"), IDLE);
	AddImage(LoadTexture((char*)"images/Player_3.png"), IDLE);
	Actor::AnimImages = GetAnimImages(Player::GetState());//基底クラスの画像配列を初期化する。

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
	AddImage(LoadTexture((char*)"images/Player_Walk_1.png"), WALK);
	/*AddImage(LoadTexture((char*)"images/Player_2.png"), WALK);
	AddImage(LoadTexture((char*)"images/Player_3.png"), WALK);*/
	AddAnimOrders(0, WALK);
	AddAnimOrders(0, WALK);
	AddAnimOrders(1, WALK);
	AddAnimOrders(2, WALK);
	AddAnimOrders(2, WALK);



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
	/*Actor* a;
	a = new GameOver(mGame, Actor::Background);
	a->SetACTOR(1000.0f, 500.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);*/


};

void Player::UpdateActor(void)
{
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);

	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//現在のグリッドから削除
		mMygrid = newMygrid;//新たなグリッドを代入
		mMygrid->addMembersIngrid(this);//更新されたグリッドに自らを追加
	}


	//========================無敵時間の処理============================//
	damageableTime++;
	if (damageableTime > 100) 
	{
		damageable = true;
	}
	//*************************無敵時間の処理オワリ*************************//


	//プレイヤのState
	enum Player::PlayerState curstate = Player::GetState();
	if (curstate != Player::GetState())//Stateが切り替わった場合
	{
		Actor::AnimImages = GetAnimImages(Player::GetState());//基盤クラスの画像配列にState毎の画像を入力し、AnimationComponent。
		Actor::AnimOrders = GetAnimOrders(Player::GetState());
	}


	//========================移動に関する処理============================//

	//現在のプレイヤの位置情報	
	D3DXVECTOR2 futurePos;
	D3DXVECTOR2 curPos;
	//D3DXVECTOR2 lastPos;
	curPos = Actor::GetPos();
	
	//if (!P_mLift == 0)
	//{
	//	isInAir = true;
	//}

	////移動方向をベクトル正規化
	D3DXVec2Normalize(&mDir, &mDir);
	mVel = mDir * mSpeed;
	mJumpVel += Actor::mGravity;//重力により減衰
	mVel.y += mJumpVel;


	////入力を受け付けた場合の将来座標
	futurePos.x = curPos.x + mVel.x;
	futurePos.y = curPos.y + mVel.y;

	////画面外への移動を禁止
	///*if (futurePos.x <= 0 || futurePos.x >= 1500)
	//{
	//	mVel.x = 0.0;
	//}*/
	////画面外の上下限界まで行くと死亡判定	
	////if (futurePos.y >= 1000 || futurePos.y <= 0)
	////{
	////	mVel.x = 0.0;
	////	//Actor::SetState(EDead);
	////}
	////*************************移動に関する処理オワリ*************************//



	////=======================接触判定処理==========================//
	for (auto actor : mMygrid->GetGridMembers())
	{
		if (actor->GetTag() == Actor::Block)
		{
			if(HitGroundCheck(futurePos, actor, this) == true)
			{

				isInAir = false;
				mVel.y = 0.0f;
				
				if (HitCheckBLK(futurePos, actor, this) == true)
				{
					   //isInAir = false;
					   //mVel.y = 0.0f;
					   mJumpVel = 0.0f;
					   //setSpeed(10.0f);
				}
			}
		}
	    else if (actor->GetTag() == Actor::Enemy) 
	    {
			//HitCheckBC(futurePos, 10, enemy->GetPos(), 10)の第２及び第３引数の値が大きすぎると、エネミー側の当たり判定が実行されない
			//つまり、エネミー側にあたる前にストップしてしまう。そもそも、Posの値をfuturePosにする必用があるのか？
			if (HitCheckBC(futurePos, 50, actor->GetPos(), 50))
			{
				mVel = { 0.0, 0.0 };
				if (damageable)
				{
					Damage(0);
					damageableTime = 0;
					damageable = false;
				}
			}
		}
	}


	////*************************接触判定処理オワリ*************************//
	mDir = { 0.0f, 0.0f };
	mPos += {mVel.x, mVel.y};
	//mActor.pos += {mVel.x, mVel.y};
	Actor::SetPos(mPos.x, mPos.y);

	//カメラ座標の更新
	float camera_x, camera_y;
	camera_x = Actor::GetPos().x - DISP_POS_X;//
	camera_y = 0.0f;

	if (camera_x < 0)//カメラが移動する左限界。プレイヤーがDISP_POS_Xより左に位置している場合はカメラは移動しない。
		camera_x = 0;
	if (camera_y < 0)
		camera_y = 0;
	if (camera_x > MAP_WIDTH_MAX)//カメラが移動する右限界即ちＭＡＰの表示限界である。これ以上プレイヤーが進んでもカメラは追随しない。
		camera_x = MAP_WIDTH_MAX;
	if (camera_y > MAP_HEIGHT_MAX)
		camera_y = MAP_HEIGHT_MAX;
	CameraComponent::SetCameraPos(camera_x, camera_y);

}

void Player::Damage(int damage)
{
	mHP -= damage;
	std::vector<class Life*> mLives = GetGame()->GetLives();
	if (!mLives.empty()) 
	{
		Life* life = mLives[0];//mLivesはVector配列のため、動的にサイズが変更されている
			life->Actor::SetState(Actor::EDead);//よって常に配列の先頭アドレスを代入し、先頭のライフを削除していく
		}
	else if (mLives.empty())
	{
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

