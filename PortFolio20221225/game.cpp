
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
// プロトタイプ宣言
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
// グローバル変数:
//*****************************************************************************
//SCENE g_Scene;
//SCENE g_NextScene;

//*****************************************************************************



void gameInit(void) {
	//背景処理の初期化
	//InitBG();

	//プレイヤーの初期化
	//InitPlayer();

	//エネミーの初期化
	//InitEnemy();

	////弾の初期化
	//InitBullet();

	////敵弾の初期化
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
	// バックバッファクリア
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//画面遷移
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

//	//背景の更新
//	UpdateBG();
//	//キャラクターの更新
//	UpdatePlayer();
//	//エネミーの更新
//	UpdateEnemy();
//	//弾の更新
//	UpdateBullet();
//	//敵弾の更新
//	UpdateEBullet();
//
//	//プレイヤーと敵のデータを受け取る
//	PLAYER* pPlayer = GetPlayer();
//	ENEMY* pEnemy = GetEnemy();
//	BULLET* pBullet = GetBullet();
//
//	//敵の数だけループする
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		//敵のi番目とプレイヤーの当たり判定を行う
////		if (HitCheckBB(pPlayer->pos, 100.0f,100.0f, 
////			pEnemy[i].pos, 100.0f,100.0f) == true)
//		if (HitCheckBCSq(pPlayer->pos, 50.0f,
//			pEnemy[i].pos, 50.0f) == true)
//		{
//			//pEnemy[i]を画面から消す
//			pEnemy[i].use = false;
//		}
//	}

	//境界箱（バウンディングボックス）の当たり判定
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
	//	//矩形Aの各辺の座標を作る
	//	float boxAminX = boxApos.x - (boxAwidth / 2);//左辺
	//	float boxAmaxX = boxApos.x + (boxAwidth / 2);//右辺
	//	float boxAminY = boxApos.y - (boxAheight / 2);//上辺
	//	float boxAmaxY = boxApos.y + (boxAheight / 2);//下辺
	//	//矩形Bの各辺の座標を作る
	//	float boxBminX = boxBpos.x - (boxBwidth / 2);//左辺
	//	float boxBmaxX = boxBpos.x + (boxBwidth / 2);//右辺
	//	float boxBminY = boxBpos.y - (boxBheight / 2);//上辺
	//	float boxBmaxY = boxBpos.y + (boxBheight / 2);//下辺

	//	//矩形Bのほうを基準に考えて、各辺で境界線をつくり、
	//	//矩形Aの反対側の辺が境界線より大きいか小さいかを判定する
	//	if (boxBminX < boxAmaxX)
	//	{
	//		if (boxBmaxX > boxAminX)
	//		{
	//			if (boxBminY < boxAmaxY)
	//			{
	//				if (boxBmaxY > boxAminY)
	//				{
	//					//4辺の判定が真であればヒットしている
	//					return true;
	//				}
	//			}
	//		}
	//	}
	//	//どこかの判定で偽となればヒットしていない
	//	return false;
	//}

	//弾と敵の当たり判定
	//敵の数だけループする
	//for (int i = 0; i < ENEMY_NUM; i++)
	//{
	//	//useフラグがオンの敵のみ判定を行う
	//	if (pEnemy[i].use == false)
	//	{
	//		continue;

	//	}

	//	//弾の数だけループする
	//	for (int n = 0; n < BULLET_NUM; n++)
	//	{
	//		//useフラグがオンの弾のみ判定を行う
	//		if (pBullet[n].use == false)
	//		{
	//			continue;

	//		}

	//		//敵のi番目と弾のn番目の当たり判定を行う
	//		if (HitCheckBCSq(pEnemy[i].pos, 50.0f,
	//			pBullet[n].pos, 50.0f) == true)
	//		{
	//			//pEnemy[i]を画面から消す
	//			pEnemy[i].use = false;
	//			//pBullet[n]を画面から消す
	//			pBullet[n].use = false;
	//		}
	//	}
	//}

	//境界円（バウンディングサークル）の当たり判定
	//bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
	//{
	//	D3DXVECTOR2 vDist;//2つの円の距離を保存する変数
	//	//	vDist.x = posB.x - posA.x;
	//	//	vDist.y = posB.y - posA.y;

	//		//２つの円を繋ぐベクトルを作る
	//	vDist = posB - posA;
	//	//作成したベクトルの大きさ（２つの円の距離）を計算する
	//	float length = D3DXVec2Length(&vDist);
	//	//２つの円の半径を足した値を作る
	//	float r = rA + rB;

	//	//距離と半径を比較し、距離のほうが大きければ当たっていない
	//	if (length > r)
	//		return false;
	//	else
	//		return true;
	//}

	////境界円（バウンディングサークル）の当たり判定2
	//bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
	//	D3DXVECTOR2 posB, float rB)
	//{
	//	D3DXVECTOR2 vDist;//2つの円の距離を保存する変数

	//	//２つの円を繋ぐベクトルを作る
	//	vDist = posB - posA;
	//	//作成したベクトルの大きさ（２つの円の距離）の２乗を計算する
	//	float length = D3DXVec2LengthSq(&vDist);
	//	//２つの円の半径を足した値の2乗を作る
	//	float r = (rA + rB) * (rA + rB);

	//	//距離と半径を比較し、距離のほうが大きければ当たっていない
	//	if (length > r)
	//		return false;
	//	else
	//		return true;
	//}
}

void gameDraw(void) {
	////背景の描画
	//DrawBG();
	////弾の描画
	//DrawBullet();
	////敵弾の描画
	//DrawEBullet();
	////敵の描画
	//DrawEnemy();
	////プレイヤーの描画
	//DrawPlayer();
};