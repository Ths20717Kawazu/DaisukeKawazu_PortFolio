#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Enemy.h"
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

Player::Player(Game* game)
	:Actor(game), mHP(100), mGame(game), mSpeed(10.0f), mPos(150.0f, 600.0f)//, mGravity(0.0f, 0.0f)
{
	//mState = ESTAND;
	//setState(ESTAND);
	//���L�R���|�l���g��new�����ƁA�e�R���|�[�l���g�z���ł�Player�iOwner�j���Ăяo����
	auto SC = new SpriteComponent(this, this);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this, this);
	SC->SetTextureID(LoadTexture((char*)"images/Player.png"));
	
	GetGame()->addPlayer(this);
}

Player::~Player() {};


void Player::DrawPlayer(void)
{
	//�L�����N�^�[�̕`��
	//�e�N�X�`�����ʎq�̃Z�b�g

}
	

void Player::UpdateActor(void) 
{
		//���݂̃v���C���̈ʒu���	
		D3DXVECTOR2 tempPos;
		D3DXVECTOR2 curPos;
		//mGravity.y += 0.1f;
		curPos = getPos();

		//�ړ��������x�N�g�����K��
		D3DXVec2Normalize(&mDir, &mDir);
		
		mVel = mDir * mSpeed;
		//���͂��󂯕t�����ꍇ�̏������W
		tempPos.x = curPos.x + mVel.x;
		tempPos.y = curPos.y + mVel.y;
		//tempPos.y = curPos.y + mVel.y + mGravity.y;
	for (auto block : GetGame()->GetBlocks())
	{
		//�������W���u���b�N�ƏՓ˂��邱�Ƃ�������ꍇ
		if (HitCheckBC(tempPos, 100, block->GetPos(), 100)) 
		{

			mVel.x = 0.0;
			mVel.y = 0.0;
			/*mGravity.y = 0.0f;
			isInAir = false;*/
		}
	
	}
	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(tempPos, 100, enemy->GetPos(), 70)) {
			mVel.x = 0.0;
			mVel.y = 0.0;
		}
	}
		mDir.y = 0.0f;
		mDir.x = 0.0f;
		mPos.x += mVel.x;
		mPos.y += mVel.y;
		//mPos.y += mVel.y + mGravity.y;
		SetPos(mPos.x, mPos.y);

	////Game�N���X���Ǘ�����S�ẴA�N�^�[�����o���A�v���C���[�ƏՓ˔�������{����B

	////�E�B���h�E�̊O�ɏo����Dead
	//VECTOR2 pos = GetPosition();
	//if (pos.x < -50 || pos.x > width + 50)
	//{
	//	SetState(EDead);
	//}
	//else
	//{
	//	//Ship�Ƃ̏Փ˔���
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
