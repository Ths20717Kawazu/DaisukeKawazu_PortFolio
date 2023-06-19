#pragma once
#include "Component.h"
//#include "Player.h"

class CameraComponent
{   
    public:
		CameraComponent();
		~CameraComponent();

		void UpdateCamera(void);
		void DrawCamera(void);
		static void GetBasePos(float* px, float* py);
		static void SetCameraPos(float x, float y);
		static D3DXVECTOR2 GetCameraPos() { return CameraPos; }
    private:
		static D3DXVECTOR2 CameraPos;
};






static Actor* mCameraOwner;

//�S�ẴA�N�^�[�ŎQ�Ƃ��邱�ƂɂȂ�֐��ł��邱�Ƃ���A�A�N�Z�X�X�R�[�v�O�Ɉȉ��̂Ƃ���L�q����B
static D3DXVECTOR2 GetPPos() { return mCameraOwner->GetPos(); }



