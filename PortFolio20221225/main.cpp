/*==============================================================================

   ゲームの初期化 [main.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "renderer.h"
#include "game.h"
//#include "input.h"
//#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************

	//Game game;

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
//SCENE g_Scene;
//SCENE g_NextScene;

//=============================================================================
// 初期化処理
//=============================================================================
//void GameInitialize(class Game* game)
//{
//	game->gameInit();
//}


//=============================================================================
// 終了処理
//=============================================================================
void GameUninitialize()
{

}


//=============================================================================
// メイン関数
//=============================================================================
void GameLoop(class Game* game)
{
	//入力の更新処理
	//UpdateInput();
	
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
	// バックバッファ、フロントバッファ入れ替え

	game->gameRunloop();

	SwapBuffers();


	//シーンの移行チェック
	//if (g_Scene != g_NextScene)
	//{
	//	switch (g_Scene)
	//	{
	//		//現在進行中のシーンを終了させる。
	//	case SCENE_TITLE:
	//		titleUninit();
	//		break;
	//	case SCENE_GAME:
	//		gameUninit();
	//		break;
	//	case SCENE_RESULT:
	//		//resultUninit();
	//		break;
	//	}

	//	//移行したシーンの初期化を行う
	//	g_Scene = g_NextScene;

	//	switch (g_Scene)
	//	{
	//		//現在進行中のシーンを終了させる。
	//	case SCENE_TITLE:
	//		titleUninit();
	//		break;
	//	case SCENE_GAME:
	//		gameUninit();
	//		break;
	//	case SCENE_RESULT:
	//		//ResultUninit();
	//		break;
	//	}

//	//}
}

