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

//�萔�錾
#define BOX_WIDTH	(100.0f) //���̕�
#define BOX_HEIGHT	(100.0f) //���̍���

//static PLAYER g_Player;
static int g_TextureChara;
static int g_AnimePtn;
static int g_AnimeWait;
static int g_Muki;

//�f�[�^�����炩���߃e�[�u��������
static float g_AnimeUV[4] =
{
	0.0f,
	0.333333f,
	0.666666f,
	0.333333f
};

Player::Player(Game* game, enum Actor::Tag tag)
	:Actor(game, tag),
	mGame(game),
	mSpeed(10.0f),
	PlayerHeight(300),
	PlayerWidth(300),
	mGravity(2.0f),
	P_mLift(0.0f),
	mJumpVel(0.0f),
	mRemainLives(5)
{
	//�e�N���X�ł���Actor��Protected�̃����o�ϐ��̏������́��̂悤�Ɏ��{����K�p������B
	mHP = 100;
	mPos = { 100.0f, 500.0f };
	animate = true;

	//���L�R���|�l���g��new�����ƁA�e�R���|�[�l���g�z���ł�Player�iOwner�j���Ăяo����
	//auto SC = new SpriteComponent(this, this);
	auto SC = new SpriteComponent(this, 600);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	//auto AC = new AnimationComponent(this, this);//Player�Ƒ��̃A�j���[�V��������L������ʂɂ��Ă������A���̕K�p���͂Ȃ�
	auto AC = new AnimationComponent(this, 600);
	auto CaC = new CameraComponent(this);

	//==================�eState���Ɏg�p����摜�����ꂼ��z��ɂ���Ă���======================//

	//�v���C����EIDLE��Ԃ̉摜
    AddImage(LoadTexture((char*)"images/Player.png"),IDLE);
	AddImage(LoadTexture((char*)"images/Player_2.png"), IDLE);
	AddImage(LoadTexture((char*)"images/Player_3.png"), IDLE);
	Actor::AnimImages = GetAnimImages(Player::GetState());//���N���X�̉摜�z�������������B

	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(0, IDLE);
	AddAnimOrders(1, IDLE);
	AddAnimOrders(2, IDLE);
	AddAnimOrders(2, IDLE);
	Actor::AnimOrders = GetAnimOrders(Player::GetState());//���N���X�̉摜�����z�������������B

	//AddAnimOrders(1, IDLE);
	//AddAnimOrders(2, IDLE);
	//AddAnimOrders(2, IDLE);


	//�v���C����EWALK��Ԃ̉摜
	//AddImage(LoadTexture((char*)"images/Player_Walk_1.png"), WALK);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EWALK);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EWALK);

	//�v���C����ERUN��Ԃ̉摜
	//AC->AddImage(LoadTexture((char*)"images/Player.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EIDLE);

	////�v���C����EJUMP��Ԃ̉摜
	//AC->AddImage(LoadTexture((char*)"images/Player.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_2.png"), EIDLE);
	//AC->AddImage(LoadTexture((char*)"images/Player_3.png"), EIDLE);

	////�v���C����EFALL��Ԃ̉摜
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
	
		//�v���C����State
	enum Player::PlayerState curstate = Player::GetState();
	if (curstate != Player::GetState())//State���؂�ւ�����ꍇ
	{
	   Actor::AnimImages = GetAnimImages(Player::GetState());//��ՃN���X�̉摜�z���State���̉摜����͂��AAnimationComponent�B
	   Actor::AnimOrders = GetAnimOrders(Player::GetState());
	}

		//���݂̃v���C���̈ʒu���	
		D3DXVECTOR2 tempPos;
		D3DXVECTOR2 curPos;
		D3DXVECTOR2 lastPos;
		curPos = getPos();
		if (!P_mLift == 0)
		{
			isInAir = true;
		}
		//�ړ��������x�N�g�����K��
		D3DXVec2Normalize(&mDir, &mDir);
		mVel = mDir * mSpeed;
		mVel.y += mJumpVel;
		mJumpVel += Actor::mGravity + P_mLift;//�d�͂ɂ�茸��

		//���͂��󂯕t�����ꍇ�̏������W
		tempPos.x = curPos.x + mVel.x;
		tempPos.y = curPos.y + mVel.y;

		//��ʊO�ւ̈ړ����֎~
		if (tempPos.x  <= 0 || tempPos.x >= 1500)
		{
			mVel.x = 0.0;
		}
		
		for (auto block : GetGame()->GetBlocks())
		{
			//�������W���u���b�N�ƏՓ˂��邱�Ƃ�������ꍇ�i���i�K�ł͏ォ��̐ڐG�̂ݑΉ��ƂȂ��Ă���j
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
			else if (HitCheckBC(tempPos, 10, block->GetPos(), 10)) 
			{
				isInAir = true;
			}
			/*else if (HitCheckBC(tempPos, 100, block->GetPos(), 100) == false)
			{
				isInAir = true;
			}*/
		}
		/*if (deltatime == 10) 
		{*/
		for (auto enemy : GetGame()->GetEnemies()) 
		{	
			//HitCheckBC(tempPos, 10, enemy->GetPos(), 10)�̑�Q�y�ё�R�����̒l���傫������ƁA�G�l�~�[���̓����蔻�肪���s����Ȃ�
			//�܂�A�G�l�~�[���ɂ�����O�ɃX�g�b�v���Ă��܂��B���������APos�̒l��tempPos�ɂ���K�p������̂��H
			if (HitCheckBC(tempPos, 50, enemy->GetPos(), 50))
			{
				//mVel = { 0.0, 0.0 };
				Damage(0);
			}

			/*if (HitCheckBC(Enemy::GetPos(), 100, GetGame()->GetPlayer()->GetPos(), 50))
			{
				GetGame()->GetPlayer()->Damage(100.0f);;
			};*/
		}
	/*		deltatime = 0;
		}*/
		//deltatime++;
		//Damage(1);
		mDir = { 0.0f, 0.0f };
		mPos += {mVel.x, mVel.y};
		SetPos(mPos.x, mPos.y);
}

void Player::Damage(int damage)
{
	mHP -= damage;
	std::vector<class Life*> mLives = GetGame()->GetLives();
	if (!mLives.empty()) 
	{
		Life* life = mLives[0];//mLives��Vector�z��̂��߁A���I�ɃT�C�Y���ύX����Ă���
		life->Actor::SetState(Actor::EDead);//�A����ď�ɔz��̐擪�A�h���X�������A�擪�̃��C�t���폜���Ă���
	}
	else if (mLives.empty())
	{
		Actor::SetState(EDead);

	}
};

//������Player��State�ɉ�����
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
//AddImage�܂ł�OK�@Vector�z��ɂ͂R�̗v�f���͂����Ă���͂��B


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



//������Player��State�ɉ����āA�摜�z���I�����ĕԂ�
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

//������Player��State�ɉ����āA�\��������I�����ĕԂ�
std::vector<int> Player::GetAnimOrders(Player::PlayerState state)
{
	switch (state)
	{
	case Player::IDLE:
		return animIdleOrders;
		break;
	}
}

