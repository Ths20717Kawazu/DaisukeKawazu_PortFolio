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
	//�����ŉ摜ID���������z�񂩂�摜ID���������o�����B
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
	//SpriteComponent::SetTextureID(mImages[idx]);// �������ƍX�V����Ă���B
	SpriteComponent::SetTextureID(mImages[AnimationComponent::GetIdx()]);
	//mImages[mCurIdx] => mImages[load texture()]
	//SetTextureID -> Draw
	//���͂����G��\������B
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
//	//�ǂݍ��܂�Ă���e�N�X�`�����𒲂ׂāA�����̂��̂�
//	//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
//	for (unsigned int i = 0; i < g_TextureIndex; i++)
//	{
//		//�e�N�X�`�������r
//		if (strcmp(g_TextureName[i], fileName) == 0)
//		{
//			return i;
//		}
//	}
//
//	//�ǂݍ��ݍő吔�𒴂��Ă����畉�̒l��Ԃ�
//	if (g_TextureIndex == MAX_TEXTURE_NUM)
//	{
//		return -1;
//	}
//
//	//�t�@�C������e�N�X�`����ǂݍ���
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
//		//�ǂݍ��݂Ɏ��s�����ꍇ�A���̒l��Ԃ�
//		return -1;
//	}
//
//	//�ǂݍ��񂾃e�N�X�`������ۑ�����
//	strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);
//
//	int retIndex = g_TextureIndex;
//
//	//�C���f�b�N�X����i�߂�
//	g_TextureIndex++;
//
//	return retIndex;
//}

