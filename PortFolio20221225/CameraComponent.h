#pragma once
#include "Component.h"
//#include "Player.h"

class CameraComponent :
    public Component
{   
    public:
      CameraComponent(class Actor*);
    private:
};

static Actor* mCameraOwner;

//�S�ẴA�N�^�[�ŎQ�Ƃ��邱�ƂɂȂ�֐��ł��邱�Ƃ���A�A�N�Z�X�X�R�[�v�O�Ɉȉ��̂Ƃ���L�q����B
static D3DXVECTOR2 GetPPos() { return mCameraOwner->GetPos(); }



