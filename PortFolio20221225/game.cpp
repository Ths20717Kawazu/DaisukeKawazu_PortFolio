
#pragma once

#include "main.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Component.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Block.h"


//========================�ǉ�======================//

#define PLAYER_HEIGHT (300.0f)
#define PLAYER_WIDTH (300.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//float frand(void);
//bool HitCheckBB(
//	D3DXVECTOR2 boxApos,
//	float boxAwidth,
//	float boxAheight,
//	D3DXVECTOR2 boxBpos,
//	float boxBwidth,
//	float boxBheight
//);
//bool HitCheckBC(D3DXVECTOR2 posA, float rA,
//	D3DXVECTOR2 posB, float rB);
//bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
//	D3DXVECTOR2 posB, float rB);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
//SCENE g_Scene;
//SCENE g_NextScene;

//*****************************************************************************

//********�f�o�b�O�p***********************************************************
//enum Actor::STATE state;
//bool hit;
//int count = 0;
//*****************************************************************************

void Game::gameInit(void) {
	Actor* a;
	a = new Player(this);
	a->SetACTOR(100.0f, 350.0f, PLAYER_HEIGHT, PLAYER_WIDTH, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	a = new Enemy(this);
	a->SetACTOR(700.0f, 300.0f, 200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	a = new Enemy(this);
	a->SetACTOR(800.0f, 100.0f, 200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	a = new Enemy(this);
	a->SetACTOR(800.0f, 500.0f, 200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	for (int i = 0; i < 20; i++) {
		a = new Block(this);
		a->SetACTOR(100.0f * i, 900.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	}


}


void Game::gameUninit(void) {

	//delete mActors.back();

}

void Game::gameUpdate(void) {
	////=======�f�o�b�O�p========//
	//for (auto enemy : mEnemies) {
	//	state = enemy->GetState();
	//	hit = enemy->hit;
	//	count = enemy->count;
	//}
	//========================//
	for (auto actor : mActors) 
	{
		if (actor->GetState() == Actor::EActive) 
		{
			actor->UpdateActor();
		}

		if (actor->GetState() == Actor::EDead)
		{
			delete actor;
		}
	}


}

void Game::gameRunloop(void) {
	
	//========@@@@@@@@while�����͂����2�d�Ń��[�v���邱�ƂɂȂ�@@@@@@@@@@@========////
	/*while (1) 
	{
	}*/
	// �o�b�N�o�b�t�@�N���A
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//�`����{
	
	gameProcessInput();
	gameDraw();
	gameUpdate();
	//�o�b�N�o�b�t�@�A
	SwapBuffers();
}

void Game::gameDraw(void) 
{
	for (auto component : mSprites)
	{
		component->Draw();
	}
};

void Game::RemoveActor(class Actor* actor) {
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}


void Game::gameProcessInput(void) {
	UpdateInput();//���͏����̍X�V����
	for (auto actor : mActors)
	{
		actor->ProcessInput();
	}

	//�����̊m�F�p
	/*if (GetKeyboardPress(DIK_SPACE)) {
		if (!mActors.empty()) {
			delete mActors.back();

		}
	}*/

}

void Game::AddActor(Actor* actor)
{
	//Update���Ȃ�A�ǉ���Update��ɉ�������
	mActors.emplace_back(actor);
}

//�Փ˔���p�ɁA�G�ƃu���b�N�𕪂��āA���ꂼ�ꔻ�肷��B
void Game::AddBlock(class Block* block) 
{
	mBlocks.emplace_back(block);
}

//�Փ˔���p�ɁA�G�ƃu���b�N�𕪂��āA���ꂼ�ꔻ�肷��B
void Game::AddEnemy(class Enemy* enemy) {

	mEnemies.emplace_back(enemy);
}

void Game::AddSprites(SpriteComponent* sprite) 
{
	mSprites.emplace_back(sprite);
}

//
//void Game::gameUpdate(void)
//{
//	// �o�b�N�o�b�t�@�N���A
//	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//	Clear();
//	//��ʑJ��
//	//switch (g_Scene)
//	//{
//	//case SCENE_TITLE:
//	//	titleDraw();
//	//	break;
//	//case SCENE_GAME:
//	//	//GameUpdate();
//	//	break;
//	//case SCENE_Update:
//	//	//ResultUpdate();
//	//	break;
//	//}
//
////	//�w�i�̍X�V
////	UpdateBG();
//// 
//
////========================================
////	//�L�����N�^�[�̍X�V
////	UpdateActor();
////========================================
//
////	//�G�l�~�[�̍X�V
////	UpdateEnemy();
////	//�e�̍X�V
////	UpdateBullet();
////	//�G�e�̍X�V
////	UpdateEBullet();
//
//
////========================================
////	//�v���C���[�ƓG�̃f�[�^���󂯎��
////	PLAYER* pPlayer = GetPlayer();
////========================================
//
//
////	ENEMY* pEnemy = GetEnemy();
////	BULLET* pBullet = GetBullet();
////
////	//�G�̐��������[�v����
////	for (int i = 0; i < ENEMY_NUM; i++)
////	{
////		//�G��i�Ԗڂƃv���C���[�̓����蔻����s��
//////		if (HitCheckBB(pPlayer->pos, 100.0f,100.0f, 
//////			pEnemy[i].pos, 100.0f,100.0f) == true)
////		if (HitCheckBCSq(pPlayer->pos, 50.0f,
////			pEnemy[i].pos, 50.0f) == true)
////		{
////			//pEnemy[i]����ʂ������
////			pEnemy[i].use = false;
////		}
////	}
//
//	//���E���i�o�E���f�B���O�{�b�N�X�j�̓����蔻��
//	//bool HitCheckBB
//	//(
//	//	D3DXVECTOR2 boxApos,
//	//	float boxAwidth,
//	//	float boxAheight,
//	//	D3DXVECTOR2 boxBpos,
//	//	float boxBwidth,
//	//	float boxBheight
//	//)
//	//{
//	//	//��`A�̊e�ӂ̍��W�����
//	//	float boxAminX = boxApos.x - (boxAwidth / 2);//����
//	//	float boxAmaxX = boxApos.x + (boxAwidth / 2);//�E��
//	//	float boxAminY = boxApos.y - (boxAheight / 2);//���
//	//	float boxAmaxY = boxApos.y + (boxAheight / 2);//����
//	//	//��`B�̊e�ӂ̍��W�����
//	//	float boxBminX = boxBpos.x - (boxBwidth / 2);//����
//	//	float boxBmaxX = boxBpos.x + (boxBwidth / 2);//�E��
//	//	float boxBminY = boxBpos.y - (boxBheight / 2);//���
//	//	float boxBmaxY = boxBpos.y + (boxBheight / 2);//����
//
//	//	//��`B�̂ق�����ɍl���āA�e�ӂŋ��E��������A
//	//	//��`A�̔��Α��̕ӂ����E�����傫�������������𔻒肷��
//	//	if (boxBminX < boxAmaxX)
//	//	{
//	//		if (boxBmaxX > boxAminX)
//	//		{
//	//			if (boxBminY < boxAmaxY)
//	//			{
//	//				if (boxBmaxY > boxAminY)
//	//				{
//	//					//4�ӂ̔��肪�^�ł���΃q�b�g���Ă���
//	//					return true;
//	//				}
//	//			}
//	//		}
//	//	}
//	//	//�ǂ����̔���ŋU�ƂȂ�΃q�b�g���Ă��Ȃ�
//	//	return false;
//	//}
//
//	//�e�ƓG�̓����蔻��
//	//�G�̐��������[�v����
//	//for (int i = 0; i < ENEMY_NUM; i++)
//	//{
//	//	//use�t���O���I���̓G�̂ݔ�����s��
//	//	if (pEnemy[i].use == false)
//	//	{
//	//		continue;
//
//	//	}
//
//	//	//�e�̐��������[�v����
//	//	for (int n = 0; n < BULLET_NUM; n++)
//	//	{
//	//		//use�t���O���I���̒e�̂ݔ�����s��
//	//		if (pBullet[n].use == false)
//	//		{
//	//			continue;
//
//	//		}
//
//	//		//�G��i�Ԗڂƒe��n�Ԗڂ̓����蔻����s��
//	//		if (HitCheckBCSq(pEnemy[i].pos, 50.0f,
//	//			pBullet[n].pos, 50.0f) == true)
//	//		{
//	//			//pEnemy[i]����ʂ������
//	//			pEnemy[i].use = false;
//	//			//pBullet[n]����ʂ������
//	//			pBullet[n].use = false;
//	//		}
//	//	}
//	//}
//
//	//���E�~�i�o�E���f�B���O�T�[�N���j�̓����蔻��
//	//bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
//	//{
//	//	D3DXVECTOR2 vDist;//2�̉~�̋�����ۑ�����ϐ�
//	//	//	vDist.x = posB.x - posA.x;
//	//	//	vDist.y = posB.y - posA.y;
//
//	//		//�Q�̉~���q���x�N�g�������
//	//	vDist = posB - posA;
//	//	//�쐬�����x�N�g���̑傫���i�Q�̉~�̋����j���v�Z����
//	//	float length = D3DXVec2Length(&vDist);
//	//	//�Q�̉~�̔��a�𑫂����l�����
//	//	float r = rA + rB;
//
//	//	//�����Ɣ��a���r���A�����̂ق����傫����Γ������Ă��Ȃ�
//	//	if (length > r)
//	//		return false;
//	//	else
//	//		return true;
//	//}
//
//	////���E�~�i�o�E���f�B���O�T�[�N���j�̓����蔻��2
//	//bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
//	//	D3DXVECTOR2 posB, float rB)
//	//{
//	//	D3DXVECTOR2 vDist;//2�̉~�̋�����ۑ�����ϐ�
//
//	//	//�Q�̉~���q���x�N�g�������
//	//	vDist = posB - posA;
//	//	//�쐬�����x�N�g���̑傫���i�Q�̉~�̋����j�̂Q����v�Z����
//	//	float length = D3DXVec2LengthSq(&vDist);
//	//	//�Q�̉~�̔��a�𑫂����l��2������
//	//	float r = (rA + rB) * (rA + rB);
//
//	//	//�����Ɣ��a���r���A�����̂ق����傫����Γ������Ă��Ȃ�
//	//	if (length > r)
//	//		return false;
//	//	else
//	//		return true;
//	//}
//}