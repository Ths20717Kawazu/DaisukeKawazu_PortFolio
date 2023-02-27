#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player), mInterval(10)
{

}


void AnimationComponent::AddImage(int img) {

	mImages.emplace_back(img);
}

void AnimationComponent::Update() 
{
	
	mTimer++;
	/*if (mTimer >= 10) 
	{
		mTimer = 0;
	}*/
	if (mTimer == mInterval) 
	{
		mTimer = 0;
		idx = GetIdx();
		idx++;
		SetIdx(idx);
		
		if (AnimationComponent::GetIdx() == mImages.size())
		{
			SetIdx(0);
		}
	}
}

void AnimationComponent::Draw() 
{
	//ここで画像IDが入った配列から画像IDが順次取り出される。
	/*idx++;
	if (idx >= 3) {
		idx = 0;
	}*/
	mTimer++;
	/*if (mTimer >= 10)
	{
		mTimer = 0;
	}*/
	if (mTimer == mInterval)
	{
		mTimer = 0;
		idx = GetIdx();
		idx++;
		SetIdx(idx);

		if (AnimationComponent::GetIdx() == mImages.size())
		{
			SetIdx(0);
		}
	}
	//SpriteComponent::SetTextureID(mImages[idx]);// ←ちゃんと更新されている。
	SpriteComponent::SetTextureID(mImages[AnimationComponent::GetIdx()]);
	//mImages[mCurIdx] => mImages[load texture()]
	//SetTextureID -> Draw
	//入力した絵を表示する。
	SpriteComponent::Draw();
}


//void AnimSpriteComponent::Draw()
//{
//	SetImage(mImgs[mCurIdx]);
//	SpriteComponent::Draw();
//}


//SetTextureID(LoadTexture((char*)"images/Player.png"));
// 
//void SetTextureID(int tID) { TextureID = tID; }

//int LoadTexture(char* fileName)
//{
//	//読み込まれているテクスチャ名を調べて、同名のものが
//	//すでに読み込まれていたらその番号を返す
//	for (unsigned int i = 0; i < g_TextureIndex; i++)
//	{
//		//テクスチャ名を比較
//		if (strcmp(g_TextureName[i], fileName) == 0)
//		{
//			return i;
//		}
//	}
//
//	//読み込み最大数を超えていたら負の値を返す
//	if (g_TextureIndex == MAX_TEXTURE_NUM)
//	{
//		return -1;
//	}
//
//	//ファイルからテクスチャを読み込む
//	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
//		GetDevice(),
//		fileName,
//		NULL,
//		NULL,
//		&g_pTexture[g_TextureIndex],
//		NULL);
//
//	if (S_OK != hr)
//	{
//		//読み込みに失敗した場合、負の値を返す
//		return -1;
//	}
//
//	//読み込んだテクスチャ名を保存する
//	strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);
//
//	int retIndex = g_TextureIndex;
//
//	//インデックスを一つ進める
//	g_TextureIndex++;
//
//	return retIndex;
//}

