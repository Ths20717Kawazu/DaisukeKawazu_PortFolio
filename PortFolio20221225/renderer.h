/*==============================================================================

   レンダリング管理[renderer.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"

//*********************************************************
// 構造体
//*********************************************************

// 頂点構造体
struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXCOLOR  Diffuse;
	D3DXVECTOR2 TexCoord;
};


// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16byte境界用
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);
HWND GetHWND(void);

void Clear(void);
void ClearColor(float r, float g, float b, float a);
void SwapBuffers(void);

ID3D11Device* GetDevice(void);
ID3D11DeviceContext* GetDeviceContext(void);

void SetDepthEnable(bool Enable);

void SetWorldViewProjection2D(void);
void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
void SetViewMatrix(D3DXMATRIX* ViewMatrix);
void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
void SetMaterial(MATERIAL Material);
void SetDebugString(char* str);
