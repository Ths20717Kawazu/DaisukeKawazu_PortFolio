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

//全てのアクターで参照することになる関数であることから、アクセススコープ外に以下のとおり記述する。
static D3DXVECTOR2 GetPPos() { return mCameraOwner->GetPos(); }



