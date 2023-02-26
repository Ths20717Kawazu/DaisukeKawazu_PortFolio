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
	0.333333f,
};

Player::Player(Game* game, int tagID)
	:Actor(game, tagID), 
	mHP(100), 
	mGame(game), 
	mSpeed(10.0f), 
	mPos(100.0f, 500.0f), 
	PlayerHeight(300), 
	PlayerWidth(300), 
	mGravity(2.0f),
	P_mLift(0.0f),
	mJumpVel(0.0f)
{
	//���L�R���|�l���g��new�����ƁA�e�R���|�[�l���g�z���ł�Player�iOwner�j���Ăяo����
	auto SC = new SpriteComponent(this, this);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this, this);
	SC->SetTextureID(LoadTexture((char*)"images/Player.png"));	
	GetGame()->AddPlayer(this);
}

Player::~Player() {};


void Player::DrawPlayer(void)
{

}
	

void Player::UpdateActor(void) 
{
		//���݂̃v���C���̈ʒu���	
		D3DXVECTOR2 tempPos;
		D3DXVECTOR2 curPos;
		D3DXVECTOR2 lastPos;
		//mGravity.y += 0.1f;
		curPos = getPos();

		//�ړ��������x�N�g�����K��
		D3DXVec2Normalize(&mDir, &mDir);
		
		mVel = mDir * mSpeed;
		mVel.y += mGravity;
		//mVel.y += GetLift();
		//mVel.y += -100.0f;

		mVel.y += mJumpVel;
		//mVel.y -= mJumpVel - 5.0f;
		mJumpVel += mGravity;

		//���͂��󂯕t�����ꍇ�̏������W
		tempPos.x = curPos.x + mVel.x;
		tempPos.y = curPos.y + mVel.y;
		//tempPos.y = curPos.y + mVel.y + mGravity.y;

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
				//lastPos = getPos();
				//mVel.x = 0.0;�@
				mVel.y = 0.0f;
				mJumpVel = 0.0f;
				isInAir = false;
				setSpeed(10.0f);
			}
		}
		for (auto enemy : GetGame()->GetEnemies()) 
		{	
			//HitCheckBC(tempPos, 10, enemy->GetPos(), 10)�̑�Q�y�ё�R�����̒l���傫������ƁA�G�l�~�[���̓����蔻�肪���s����Ȃ�
			//�܂�A�G�l�~�[���ɂ�����O�ɃX�g�b�v���Ă��܂��B���������APos�̒l��tempPos�ɂ���K�p������̂��H
			if (HitCheckBC(tempPos, 10, enemy->GetPos(), 10)) {
				mVel.x = 0.0;
				mVel.y = 0.0;
				//Actor::SetState(EDead);
			}
		}
		for (auto enemy : GetGame()->GetEnemies())
		{
			//�߂��ɑ��݂���G�̔z����쐬����B
			if (HitCheckBC(tempPos, 10, enemy->GetPos(), 10)) 
			{
				SetClosetoEnemy(true);
				AddTagIDs(enemy);
			}
			else
			{
				RemoveTagIDs(enemy);
				if (mTagIDs.empty()) 
				{
					SetClosetoEnemy(false);
				}
			}

		}
		mDir.y = 0.0f;
		mDir.x = 0.0f;
		mPos.x += mVel.x;
		mPos.y += mVel.y;
		SetPos(mPos.x, mPos.y);

}
void Player::Damage(int damage)
{
	mHP -= damage;
	if (mHP <= 0) {
		Actor::SetState(EDead);
	}
};


void Player::AddTagIDs(class Enemy* enemy)
{
	mTagIDs.emplace_back(enemy);
}

void Player::RemoveTagIDs(class Enemy* enemy)
{
	auto iter = std::find(mTagIDs.begin(), mTagIDs.end(), enemy);
	if (iter != mTagIDs.end()) {
		std::iter_swap(iter, mTagIDs.end() - 1);
		mTagIDs.pop_back();
	}
}
