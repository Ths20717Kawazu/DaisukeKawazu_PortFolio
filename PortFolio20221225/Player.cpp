#include "Game.h"
#include "Player.h"
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
	:Actor(game), mHP(100), mGame(game), mSpeed(10.0f), playerPos(100.0f, 100.0f)
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
	D3DXVECTOR2 lastpos;
	lastpos = GetPos();
	

	//Game�N���X���Ǘ�����S�ẴA�N�^�[�����o���A�v���C���[�ƏՓ˔�������{����B
	for (auto enemy : GetGame()->GetActors()) 
	{
		if (HitCheckBC(GetPos(), 50, enemy->GetPos(), 50)) {
			//Damage();

		}

		//SetPos(GetACTOR().pos.x, GetACTOR().pos.y);

	}
	//HitCheckBC()

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
