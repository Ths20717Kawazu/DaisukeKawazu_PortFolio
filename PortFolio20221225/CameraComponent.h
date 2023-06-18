#pragma once
#include "Component.h"
//#include "Player.h"

class CameraComponent :
    public Component
{   
    public:
        void InitCamera(void);
		void UninitCamera(void);
		void UpdateCamera(void);
		void DrawCamera(void);
		static void SetCamera(float x, float y);
		static void GetBasePos(float* px, float* py);

        //CameraComponent(class Actor*);

    private:

};






static Actor* mCameraOwner;

//�S�ẴA�N�^�[�ŎQ�Ƃ��邱�ƂɂȂ�֐��ł��邱�Ƃ���A�A�N�Z�X�X�R�[�v�O�Ɉȉ��̂Ƃ���L�q����B
static D3DXVECTOR2 GetPPos() { return mCameraOwner->GetPos(); }



