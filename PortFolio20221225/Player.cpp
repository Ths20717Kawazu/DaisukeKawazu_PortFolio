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


/*
������������������������������������������
���R���X�g���N�^

��UpdateActor
1.�ړ�����
2.���G����
3.�ڐG����
4.�A�j���[�V����
������������������������������������������
*/

//�萔�錾
#define BOX_WIDTH	(100.0f) //���̕�
#define BOX_HEIGHT	(100.0f) //���̍���
#define DISP_POS_X	(960.0f)	//�v���C���[�\�����WX
#define DISP_POS_Y	(540.0f)	//�v���C���[�\�����WY
#define MAP_WIDTH_MAX	(2500.0f) //MAP�̉E���E
#define MAP_HEIGHT_MAX	(2000.0f) //MAP�̍������E



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

Player::Player(Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot)
	:Actor(game, tag),
	mGame(game),
	mSpeed(10.0f),
	mRemainLives(5)
{
	//�e�N���X�ł���Actor��Protected�̃����o�ϐ��̏������́��̂悤�Ɏ��{����K�p������B
	mHP = 100;
	//mPos = { 100.0f, 200.0f };
	animate = true;
	SetACTOR(posX, posY, BoxH, BoxW, UvU, UvV, VH, VW, Rot);
	mPos = { posX, posY };
	//Grid�ւ̓o�^
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);
	
	//���L�R���|�l���g��new�����ƁA�e�R���|�[�l���g�z���ł�Player�iOwner�j���Ăяo����
	//auto SC = new SpriteComponent(this, this);
	auto SC = new SpriteComponent(this, 600);
	auto IC = new InputComponent(this, this);
	auto CC = new CollisionComponent(this);
	//auto AC = new AnimationComponent(this, this);//Player�Ƒ��̃A�j���[�V��������L������ʂɂ��Ă������A���̕K�p���͂Ȃ�
	auto AC = new AnimationComponent(this, 600);

	//��������������������������������������������������������������������������������������������������������������������������������//

	//==================�eState���Ɏg�p����摜�����ꂼ��z��ɂ���Ă���======================//

	//�v���C����EIDLE��Ԃ̉摜
    AddImage(LoadTexture((char*)"images/Player.png"),IDLE);
	AddImage(LoadTexture((char*)"images/Player_2.png"), IDLE);
	AddImage(LoadTexture((char*)"images/Player_3.png"), IDLE);
	Actor::AnimImages = GetAnimImages(Player::GetState());//���N���X�̉摜�z�������������B

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
	AddImage(LoadTexture((char*)"images/Player_Walk_1.png"), WALK);
	/*AddImage(LoadTexture((char*)"images/Player_2.png"), WALK);
	AddImage(LoadTexture((char*)"images/Player_3.png"), WALK);*/
	AddAnimOrders(0, WALK);
	AddAnimOrders(0, WALK);
	AddAnimOrders(1, WALK);
	AddAnimOrders(2, WALK);
	AddAnimOrders(2, WALK);

	//�v���C����ERUN��Ԃ̉摜
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
	//�����������������������������������������������������p�[�e�B�V��������������������������������������������������//
	Actor::GetPos();
	Grid* newMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	if (mMygrid != newMygrid)
	{
		mMygrid->removeMembersIngrid(this);//���݂̃O���b�h����폜
		mMygrid = newMygrid;//�V���ȃO���b�h����
		mMygrid->addMembersIngrid(this);//�X�V���ꂽ�O���b�h�Ɏ����ǉ�
	}

	//�������������������������������������������������������G���Ԃ̏�������������������������������������������������//

	damageableTime++;
	if (damageableTime > 100) 
	{
		damageable = true;
	}
	
	//�����������������������������������������A�j���[�V�����̏���������������������������������������������������������������//


	//�v���C����State
	enum Player::PlayerState curstate = Player::GetState();
	if (curstate != Player::GetState())//State���؂�ւ�����ꍇ
	{
		Actor::AnimImages = GetAnimImages(Player::GetState());//��ՃN���X�̉摜�z���State���̉摜����͂��AAnimationComponent�B
		Actor::AnimOrders = GetAnimOrders(Player::GetState());
	}



	//�����������������������������������������������ړ��Ɋւ��鏈��������������������������������������������������������//
	int PushBack = 0;
	//���݂̃v���C���̈ʒu���	
	
	//D3DXVECTOR2 lastPos;
	curPos = Actor::GetPos();
	
	////�ړ��������x�N�g�����K��
	D3DXVec2Normalize(&mDir, &mDir);
	mVel = mDir * mSpeed;

	for (auto actor : mMygrid->GetGridMembers())
	{
		//=========================================//
		if (actor->GetTag() == Actor::Block)
		{
			if (!actor->GetPos().y == (Actor::GetPos().y + ((PlayerHeight / 2) + (Actor::BlockHeight / 2))))
			{
				break;
			}
			else
			{
				setIsInAir(true);
			}
		}
	}

	if (isInAir) 
	{
		setGravity(1.0f);
	}
	else
	{
		//setGravity(0.0f);
		SetJumpVel(0.0f);
	}
	
	//�����ւ̊ђʑ΍�Ƃ��āA�������ւ̉����x�ɐ�����݂����B
	mJumpVel += Actor::mGravity;//�d�͂ɂ�茸��
	if (mJumpVel >= 10.0f) {mJumpVel = 10.0f;}

	mVel.y += mJumpVel;

	if (hasBalloon) 
	{	mVel.y += P_mLift;	}
	//mVel.y += P_mLift;
	if (mVel.y >= 10.0f) {mVel.y = 10.0f;}
	
	//���n�ʂƂ̐ڐG���肪����Ɏ��{����Ȃ��ꍇ�A������mJumpVel�����債�A���鎞�_�Œn�ʂ��ђʂ��ĉ�ʊO�ɏo�錻�ۂ���������
	//2023/06/22

	////���͂��󂯕t�����ꍇ�̏������W
 	futurePos.x = curPos.x + mVel.x;
	futurePos.y = curPos.y + mVel.y;


	//��������������������������������������������������������������������������������������������������������������������������������//
	////=======================�ڐG���菈��==========================//
	{
		for (auto actor : mMygrid->GetGridMembers())
		{
			//=========================================//
			if (actor->GetTag() == Actor::Block)
			{
				HitCheckBLK(&futurePos, actor, this);
			}
			//=========================================//
			else if (actor->GetTag() == Actor::Enemy) 
			{
				//HitCheckBC(futurePos, 10, enemy->GetPos(), 10)�̑�Q�y�ё�R�����̒l���傫������ƁA�G�l�~�[���̓����蔻�肪���s����Ȃ�
				//�܂�A�G�l�~�[���ɂ�����O�ɃX�g�b�v���Ă��܂��B���������APos�̒l��futurePos�ɂ���K�p������̂��H
				if (HitCheckBC(curPos, 50, actor->GetPos(), 50))
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

	}


	////*************************�ڐG���菈���I����*************************//


	//mVel = futurePos;//�߂荞�݂���������futurePos��Vel�ɑ���A����ɂ��mVel�͏C�����ꂽ�ړ��ʂɍX�V�ƂȂ�
	////�����̃R�����g�A�E�g���O����vector�ŃG���[����������B���������� =>�@�}���ɐ��l�����債�����߁B
	//�����́A�����x�ł���mVel�ɍ��W���������Ă������� = futurePos
	//mPos += {mVel.x, mVel.y};//�X�V���邱�Ƃɂ��A�v���C���̍��W���ς��
     
	mDir = { 0.0f, 0.0f };//�s�xDI�����O�ɖ߂��Ȃ��ƈ�x���͂��������ւ����Ɛi��ł������ƂɂȂ�

	mPos = { futurePos.x, futurePos.y };

	Actor::SetPos(mPos.x, mPos.y);
	

	////*************************�ړ��Ɋւ��鏈���I����*************************//

	//mActor.pos += {mVel.x, mVel.y};


	//�J�������W�̍X�V
	float camera_x, camera_y;
	camera_x = Actor::GetPos().x - DISP_POS_X;//
	camera_y = 0.0f;

	if (camera_x < 0)//�J�������ړ����鍶���E�B�v���C���[��DISP_POS_X��荶�Ɉʒu���Ă���ꍇ�̓J�����͈ړ����Ȃ��B
		camera_x = 0;
	if (camera_y < 0)
		camera_y = 0;
	if (camera_x > MAP_WIDTH_MAX)//�J�������ړ�����E���E�����l�`�o�̕\�����E�ł���B����ȏ�v���C���[���i��ł��J�����͒ǐ����Ȃ��B
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
		Life* life = mLives[0];//mLives��Vector�z��̂��߁A���I�ɃT�C�Y���ύX����Ă���
			life->Actor::SetState(Actor::EDead);//����ď�ɔz��̐擪�A�h���X�������A�擪�̃��C�t���폜���Ă���
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



	////��ʊO�ւ̈ړ����֎~
	///*if (futurePos.x <= 0 || futurePos.x >= 1500)
	//{
	//	mVel.x = 0.0;
	//}*/
	////��ʊO�̏㉺���E�܂ōs���Ǝ��S����	
	////if (futurePos.y >= 1000 || futurePos.y <= 0)
	////{
	////	mVel.x = 0.0;
	////	//Actor::SetState(EDead);
	////}
				//if(actor->GetPos().y == (Actor::GetPos().y + ((PlayerHeight / 2) + (Actor::BlockHeight/2))))
				//{
				//	//setIsInAir(false);
				//	break;
				//}
				//else
				//{
				//	setIsInAir(true);
				//}

				
				/*if(HitGroundCheck(actor, this) == true)
				{
					isInAir = false;
					setGravity(0.0f);
				}
				else if (HitGroundCheck(actor, this) == false)
				{
					isInAir = true;
				}*/