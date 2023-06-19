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

//全てのアクターで参照することになる関数であることから、アクセススコープ外に以下のとおり記述する。
static D3DXVECTOR2 GetPPos() { return mCameraOwner->GetPos(); }



