#pragma once
#include "game.h"
#include "CameraComponent.h"


static float g_CameraX;
static float g_CameraY;

D3DXVECTOR2 CameraComponent::CameraPos;

CameraComponent::CameraComponent()
{
	CameraPos = { 0.0f, 0.0f };

}
CameraComponent::~CameraComponent() {}

void CameraComponent::UpdateCamera(void)
{

}

void CameraComponent::DrawCamera(void)
{

}

void CameraComponent::SetCameraPos(float x, float y) 
{
	CameraPos.x = x;
	CameraPos.y = y;
}

void CameraComponent::GetBasePos(float* px, float* py)
{
	//�J�������W�𔽓]�����l���G��`�悷���̍��W�ƂȂ�
	//*px = -g_CameraX;
	//*py = -g_CameraY;

	*px = -CameraPos.x;
	*py = -CameraPos.y;
}

//void CameraComponent::SetCamera(float x, float y)
//{
//	//�J�����̍��W���Z�b�g����
//	g_CameraX = x;
//	g_CameraY = y;
//}






//
//CameraComponent::CameraComponent(class Actor* Owner): Component(Owner)
//{
//	mCameraOwner = Owner;
//}


