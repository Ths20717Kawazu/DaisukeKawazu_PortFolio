#include "SpriteComponent.h"
//#include "AnimationComponent.h"
#include "Actor.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

//
//SpriteComponent::SpriteComponent(class Actor* Owner, class Player* Player) :Component(Owner, Player)
//{
//	InitSprite();
//	mOwner->GetGame()->AddSprites(this);
//}


SpriteComponent::SpriteComponent(class Actor* Owner):Component(Owner)
{
	InitSprite();
	mOwner->GetGame()->AddSprites(this);

}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
	//UninitSprite();
}



static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_���
static unsigned int	g_Texture = 0;

void SpriteComponent::InitSprite(void)
{
	g_Texture = 0;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

void SpriteComponent::UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void SpriteComponent::DrawSprite(float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);//���_���i�������̈�j���V�F�[�_�ɂ킽��

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//TextureNo�͂Ȃɂ������Ă��Ȃ��ꍇ�́[�P���Ԃ�͂��B�P�������ǂݍ���ł���Ȃ�O�ł����Ȃ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureID));

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	//���_�̏��
	vertex[0].Position = D3DXVECTOR3(x - (width / 2), y - (height / 2), 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@�����
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(u, v);

	vertex[1].Position = D3DXVECTOR3(x + (width / 2), y - (height / 2), 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(u + uw, v);

	vertex[2].Position = D3DXVECTOR3(x - (width / 2), y + (height / 2), 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(u, v + vh);

	vertex[3].Position = D3DXVECTOR3(x + (width / 2), y + (height / 2), 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(u + uw, v + vh);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// �|���S���`��
	// ������draw��DirectX�̊֐�
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteRotate(float x, float y, float width, float height, float u, float v, float uw, float vh, float rot)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;//���̔����A�����̔���
	hw = width / 2;
	hh = height / 2;
	float BaseAngle = atan2(hh, hw);//���ƍ����̔䂩��p�x���v�Z����
	float r;
	r = sqrtf((width / 2) * (width / 2) + (width / 2) * (width / 2));

	//X = x���W + cos(�p�x)*���a
	//Y = y���W + sin(�p�x)*���a
	float rotx, roty;
	rotx = x - cosf(BaseAngle + rot) * r;
	roty = y - sinf(BaseAngle + rot) * r;
	vertex[0].Position = D3DXVECTOR3(rotx, roty, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(u, v);

	rotx = x + cosf(BaseAngle - rot) * r;
	roty = y - sinf(BaseAngle - rot) * r;
	vertex[1].Position = D3DXVECTOR3(rotx, roty, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(u + uw, v);

	rotx = x - cosf(BaseAngle - rot) * r;
	roty = y + sinf(BaseAngle - rot) * r;
	vertex[2].Position = D3DXVECTOR3(rotx, roty, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(u, v + vh);

	rotx = x + cosf(BaseAngle + rot) * r;
	roty = y + sinf(BaseAngle + rot) * r;
	vertex[3].Position = D3DXVECTOR3(rotx, roty, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(u + uw, v + vh);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteLeftTop(float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(u, v);

	vertex[1].Position = D3DXVECTOR3(x + width, y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(u + uw, v);

	vertex[2].Position = D3DXVECTOR3(x, y + height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(u, v + vh);

	vertex[3].Position = D3DXVECTOR3(x + width, y + height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(u + uw, v + vh);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteColor(float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(r, g, b, a);
	SetMaterial(material);

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(x - (width / 2), y - (height / 2), 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(u, v);

	vertex[1].Position = D3DXVECTOR3(x + (width / 2), y - (height / 2), 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(u + uw, v);

	vertex[2].Position = D3DXVECTOR3(x - (width / 2), y + (height / 2), 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(u, v + vh);

	vertex[3].Position = D3DXVECTOR3(x + (width / 2), y + (height / 2), 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(u + uw, v + vh);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}


//======2023/1/22 Draw�֐����I�[�o�[���[�h�ɂ��āADrawSprite�����ω����Ă��@�\����悤�ɂ�����=======//
void SpriteComponent::Draw() {
	//DrawSprite�ɓn���̂ɕK�p�Ȉ������擾����B
	float x = mOwner->GetACTOR().pos.x;
	float y = mOwner->GetACTOR().pos.y;
	float width = mOwner->GetACTOR().mBoxWidth;
	float height = mOwner->GetACTOR().mBoxHeight;
	float u = mOwner->GetACTOR().mUvpositionU;
	float v = mOwner->GetACTOR().mUvpositionV;
	float uw = mOwner->GetACTOR().mUWidth;
    float vh = mOwner->GetACTOR().mVHeight;
	//DrawSprite����TextureID�����͂���Ă���B
	DrawSprite(x, y, width, height, u, v, uw, vh);
}

//Animation���Ȃ��A�N�^�[�ɂ��Ă͂����炪�K�p�����B
//�ǂ����Ă�Player�����Q�d�ŕ`�悳��Ă��܂��̂ŁA�s���R�ł��邪�֐����ŏ������������āA
//�A�j���[�V�������Ȃ��A�N�^�̏ꍇ�Ɏ��s�����悤�ɂ���
void SpriteComponent::StaticDraw() {
	float x = mOwner->GetACTOR().pos.x;
	float y = mOwner->GetACTOR().pos.y;
	float width = mOwner->GetACTOR().mBoxWidth;
	float height = mOwner->GetACTOR().mBoxHeight;
	float u = mOwner->GetACTOR().mUvpositionU;
	float v = mOwner->GetACTOR().mUvpositionV;
	float uw = mOwner->GetACTOR().mUWidth;
	float vh = mOwner->GetACTOR().mVHeight;
	//DrawSprite����TextureID�����͂���Ă���B
	if (mOwner->getAnimate() == false) {
		DrawSprite(x, y, width, height, u, v, uw, vh);

	}
}


//Spritcomp::UpdateDraw->AnimationComponent::UpdateImage()->SpriteComp::Draw