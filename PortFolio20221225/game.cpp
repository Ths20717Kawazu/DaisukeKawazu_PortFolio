
#pragma once

#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
//#include "bg.h"
#include "sprite.h"
//#include "player.h"
//#include "enemy.h"
//#include "bullet.h"
//#include "enemybullet.h"
//#include "title.h"

#include "game.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);
bool HitCheckBB(
	D3DXVECTOR2 boxApos,
	float boxAwidth,
	float boxAheight,
	D3DXVECTOR2 boxBpos,
	float boxBwidth,
	float boxBheight
);
bool HitCheckBC(D3DXVECTOR2 posA, float rA,
	D3DXVECTOR2 posB, float rB);
bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
	D3DXVECTOR2 posB, float rB);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
//SCENE g_Scene;
//SCENE g_NextScene;

//*****************************************************************************



void gameInit(void) {
	//�w�i�����̏�����
	//InitBG();

	//�v���C���[�̏�����
	//InitPlayer();

	//�G�l�~�[�̏�����
	//InitEnemy();

	////�e�̏�����
	//InitBullet();

	////�G�e�̏�����
	//InitEBullet();
}


void gameUninit(void) {
	/*UninitEBullet();

	UninitBullet();

	UninitEnemy();

	UninitPlayer();

	UninitBG();*/
}


void gameUpdate(void)
{
	// �o�b�N�o�b�t�@�N���A
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//��ʑJ��
	//switch (g_Scene)
	//{
	//case SCENE_TITLE:
	//	titleDraw();
	//	break;
	//case SCENE_GAME:
	//	//GameUpdate();
	//	break;
	//case SCENE_Update:
	//	//ResultUpdate();
	//	break;
	//}

//	//�w�i�̍X�V
//	UpdateBG();
//	//�L�����N�^�[�̍X�V
//	UpdatePlayer();
//	//�G�l�~�[�̍X�V
//	UpdateEnemy();
//	//�e�̍X�V
//	UpdateBullet();
//	//�G�e�̍X�V
//	UpdateEBullet();
//
//	//�v���C���[�ƓG�̃f�[�^���󂯎��
//	PLAYER* pPlayer = GetPlayer();
//	ENEMY* pEnemy = GetEnemy();
//	BULLET* pBullet = GetBullet();
//
//	//�G�̐��������[�v����
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		//�G��i�Ԗڂƃv���C���[�̓����蔻����s��
////		if (HitCheckBB(pPlayer->pos, 100.0f,100.0f, 
////			pEnemy[i].pos, 100.0f,100.0f) == true)
//		if (HitCheckBCSq(pPlayer->pos, 50.0f,
//			pEnemy[i].pos, 50.0f) == true)
//		{
//			//pEnemy[i]����ʂ������
//			pEnemy[i].use = false;
//		}
//	}

	//���E���i�o�E���f�B���O�{�b�N�X�j�̓����蔻��
	//bool HitCheckBB
	//(
	//	D3DXVECTOR2 boxApos,
	//	float boxAwidth,
	//	float boxAheight,
	//	D3DXVECTOR2 boxBpos,
	//	float boxBwidth,
	//	float boxBheight
	//)
	//{
	//	//��`A�̊e�ӂ̍��W�����
	//	float boxAminX = boxApos.x - (boxAwidth / 2);//����
	//	float boxAmaxX = boxApos.x + (boxAwidth / 2);//�E��
	//	float boxAminY = boxApos.y - (boxAheight / 2);//���
	//	float boxAmaxY = boxApos.y + (boxAheight / 2);//����
	//	//��`B�̊e�ӂ̍��W�����
	//	float boxBminX = boxBpos.x - (boxBwidth / 2);//����
	//	float boxBmaxX = boxBpos.x + (boxBwidth / 2);//�E��
	//	float boxBminY = boxBpos.y - (boxBheight / 2);//���
	//	float boxBmaxY = boxBpos.y + (boxBheight / 2);//����

	//	//��`B�̂ق�����ɍl���āA�e�ӂŋ��E��������A
	//	//��`A�̔��Α��̕ӂ����E�����傫�������������𔻒肷��
	//	if (boxBminX < boxAmaxX)
	//	{
	//		if (boxBmaxX > boxAminX)
	//		{
	//			if (boxBminY < boxAmaxY)
	//			{
	//				if (boxBmaxY > boxAminY)
	//				{
	//					//4�ӂ̔��肪�^�ł���΃q�b�g���Ă���
	//					return true;
	//				}
	//			}
	//		}
	//	}
	//	//�ǂ����̔���ŋU�ƂȂ�΃q�b�g���Ă��Ȃ�
	//	return false;
	//}

	//�e�ƓG�̓����蔻��
	//�G�̐��������[�v����
	//for (int i = 0; i < ENEMY_NUM; i++)
	//{
	//	//use�t���O���I���̓G�̂ݔ�����s��
	//	if (pEnemy[i].use == false)
	//	{
	//		continue;

	//	}

	//	//�e�̐��������[�v����
	//	for (int n = 0; n < BULLET_NUM; n++)
	//	{
	//		//use�t���O���I���̒e�̂ݔ�����s��
	//		if (pBullet[n].use == false)
	//		{
	//			continue;

	//		}

	//		//�G��i�Ԗڂƒe��n�Ԗڂ̓����蔻����s��
	//		if (HitCheckBCSq(pEnemy[i].pos, 50.0f,
	//			pBullet[n].pos, 50.0f) == true)
	//		{
	//			//pEnemy[i]����ʂ������
	//			pEnemy[i].use = false;
	//			//pBullet[n]����ʂ������
	//			pBullet[n].use = false;
	//		}
	//	}
	//}

	//���E�~�i�o�E���f�B���O�T�[�N���j�̓����蔻��
	//bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
	//{
	//	D3DXVECTOR2 vDist;//2�̉~�̋�����ۑ�����ϐ�
	//	//	vDist.x = posB.x - posA.x;
	//	//	vDist.y = posB.y - posA.y;

	//		//�Q�̉~���q���x�N�g�������
	//	vDist = posB - posA;
	//	//�쐬�����x�N�g���̑傫���i�Q�̉~�̋����j���v�Z����
	//	float length = D3DXVec2Length(&vDist);
	//	//�Q�̉~�̔��a�𑫂����l�����
	//	float r = rA + rB;

	//	//�����Ɣ��a���r���A�����̂ق����傫����Γ������Ă��Ȃ�
	//	if (length > r)
	//		return false;
	//	else
	//		return true;
	//}

	////���E�~�i�o�E���f�B���O�T�[�N���j�̓����蔻��2
	//bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
	//	D3DXVECTOR2 posB, float rB)
	//{
	//	D3DXVECTOR2 vDist;//2�̉~�̋�����ۑ�����ϐ�

	//	//�Q�̉~���q���x�N�g�������
	//	vDist = posB - posA;
	//	//�쐬�����x�N�g���̑傫���i�Q�̉~�̋����j�̂Q����v�Z����
	//	float length = D3DXVec2LengthSq(&vDist);
	//	//�Q�̉~�̔��a�𑫂����l��2������
	//	float r = (rA + rB) * (rA + rB);

	//	//�����Ɣ��a���r���A�����̂ق����傫����Γ������Ă��Ȃ�
	//	if (length > r)
	//		return false;
	//	else
	//		return true;
	//}
}

void gameDraw(void) {
	////�w�i�̕`��
	//DrawBG();
	////�e�̕`��
	//DrawBullet();
	////�G�e�̕`��
	//DrawEBullet();
	////�G�̕`��
	//DrawEnemy();
	////�v���C���[�̕`��
	//DrawPlayer();
};