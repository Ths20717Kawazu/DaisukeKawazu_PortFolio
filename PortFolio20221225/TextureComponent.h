#pragma once
#include "Component.h"
#include "renderer.h"

/*------------------------------------------------------------------------------
   �萔��`
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
    static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM]{};	//�e�N�X�`���z��
    static unsigned int g_TextureIndex{ 0 };					// �e�N�X�`���z��̖����������C���f�b�N�X
    static char g_TextureName[MAX_TEXTURE_NUM][256]{};	// �e�N�X�`�����o�b�t�@
};

