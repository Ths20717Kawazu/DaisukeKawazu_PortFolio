#include "Player.h"
#include "SpriteComponent.h"


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
	:Actor(game)
{
	new SpriteComponent(this);

}

Player::~Player() {};


void Player::DrawPlayer(void)
{
	//�L�����N�^�[�̕`��
	//�e�N�X�`�����ʎq�̃Z�b�g

}