/*==============================================================================

   ���ʃw�b�_�[ [main.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

//#include "title.h"

#pragma warning(pop)


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���
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
// �v���g�^�C�v�錾
//*****************************************************************************

void GameInitialize(class Game* game);
void GameLoop(class Game* game);
void GameUninitialize(void);

float frand(void);
//void SetScene(SCENE next);