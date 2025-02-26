#pragma once
#include "Component.h"


//描画する順序は値の小さい順とする。基準となる順番は、背景、障害物、敵、アイテム、風船、プレイヤ、IF
//順番は上記の描画対象の左から１００ずつ増加させる。
//====================================--//
//背景：１００
//障害物：２００
//敵：３００
//アイテム：４００
//風船：５００
//プレイヤ：６００
//IF：７００
//======================================//

class SpriteComponent :
    public Component
{
    public:
        //SpriteComponent(class Actor* Owner, class Player* Player);
        SpriteComponent(Actor* actor, int draworder);
        virtual ~SpriteComponent();

        void InitSprite(void);
        void UninitSprite(void);

        void DrawSprite(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteRotate(float x, float y, float width, float height, float u, float v, float uw, float vh, float rot);
        void DrawSpriteLeftTop(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteColor(float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a);
        
        void Draw();
        void StaticDraw();//Updateされない描画

        void SetTextureID(int tID) { TextureID = tID; }
        int GetDrawOrder() { return mDrawOrder; }

        virtual void UpdateDraw() {};
       // virtual void DrawEnemy() {}; 使用していないため削除予定
        void AddAnim(class AnimationComponent* animcomp) { mAnimcomp = animcomp; }
    private:
        int TextureID;
        int mDrawOrder;
        class AnimationComponent* mAnimcomp;
       
};

