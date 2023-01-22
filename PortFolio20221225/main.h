/*==============================================================================

   共通ヘッダー [main.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

//#include "title.h"

#pragma warning(pop)


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ
#define PI (3.1415926535897932384626433832795f)

struct Float2
{
	float x;
	float y;
};

struct Float3
{
	float x;
	float y;
	float z;
};

struct Float4
{
	float x;
	float y;
	float z;
	float w;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void GameInitialize(class Game* game);
void GameLoop(class Game* game);
void GameUninitialize(void);

float frand(void);
//void SetScene(SCENE next);