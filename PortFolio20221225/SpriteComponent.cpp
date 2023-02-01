#include "SpriteComponent.h"
#include "Actor.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

SpriteComponent::SpriteComponent(class Actor* owner):Component(owner)
{
	InitSprite();

	mOwner->GetGame()->AddSprites(this);
	//画像を読み込む
	//g_TextureNo = LoadTexture((char*)"images/enemy.png");
	//テクスチャ識別子のセット
	//SetTexture(g_TextureNo);
}

SpriteComponent::~SpriteComponent() 
{
	UninitSprite();
};

static ID3D11Buffer* g_VertexBuffer = NULL;	// 頂点情報
static unsigned int	g_Texture = 0;

void SpriteComponent::InitSprite(void)
{
	g_Texture = 0;

	// 頂点バッファ生成
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
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void SpriteComponent::DrawSprite(float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));


	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureID));
	//TextureNoはなにも入っていない場合はー１が返るはず。１枚だけ読み込んでいるなら０でも問題ない

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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

	// ポリゴン描画
	// ここのdrawはDirectXの関数
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteRotate(float x, float y, float width, float height, float u, float v, float uw, float vh, float rot)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;//幅の半分、高さの半分
	hw = width / 2;
	hh = height / 2;
	float BaseAngle = atan2(hh, hw);//幅と高さの比から角度を計算する
	float r;
	r = sqrtf((width / 2) * (width / 2) + (width / 2) * (width / 2));

	//X = x座標 + cos(角度)*半径
	//Y = y座標 + sin(角度)*半径
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

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteLeftTop(float x, float y, float width, float height, float u, float v, float uw, float vh)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// マテリアル設定
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

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

void SpriteComponent::DrawSpriteColor(float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Texture));

	// マテリアル設定
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

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}


//======2023/1/22 Draw関数をオーバーロードにして、DrawSprite等が変化しても機能するようにしたい=======//
void SpriteComponent::Draw() {
	//DrawSpriteに渡すのに必用な引数を取得する。
	float x = mOwner->GetPositionX();
	float y = mOwner->GetPositionY();
	float width = mOwner->GetBoxWidth();
	float height = mOwner->GetBoxHeight();
	float u = mOwner->GetUvpositonU();
	float v = mOwner->GetUvpositonV();
	float uw = mOwner->GetUWidth();
    float vh = mOwner->GetVHeight();
	DrawSprite(x, y, width, height, u, v, uw, vh );
}
