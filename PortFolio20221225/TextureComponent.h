#pragma once
#include "Component.h"
#include "renderer.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define MAX_TEXTURE_NUM 100

class TextureComponent :
    public Component
{
    TextureComponent();
    ~TextureComponent();

    int LoadTexture(char* fileName);
    void UninitTexture(void);

    ID3D11ShaderResourceView** GetTexture(int index);

private:
    static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM]{};	//テクスチャ配列
    static unsigned int g_TextureIndex{ 0 };					// テクスチャ配列の末尾を示すインデックス
    static char g_TextureName[MAX_TEXTURE_NUM][256]{};	// テクスチャ名バッファ
};

