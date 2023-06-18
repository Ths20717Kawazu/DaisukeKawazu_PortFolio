#pragma once

#include "CameraComponent.h"




static float g_CameraX;
static float g_CameraY;

void CameraComponent::InitCamera(void)
{
	g_CameraX = 0.0f;
	g_CameraY = 0.0f;
}

void CameraComponent::UninitCamera(void)
{

}

void CameraComponent::UpdateCamera(void)
{

}

void CameraComponent::DrawCamera(void)
{

}

void CameraComponent::SetCamera(float x, float y)
{
	//カメラの座標をセットする
	g_CameraX = x;
	g_CameraY = y;
}

void CameraComponent::GetBasePos(float* px, float* py)
{
	//カメラ座標を反転した値が絵を描画する基準の座標となる
	*px = -g_CameraX;
	*py = -g_CameraY;
}





//
//CameraComponent::CameraComponent(class Actor* Owner): Component(Owner)
//{
//	mCameraOwner = Owner;
//}


