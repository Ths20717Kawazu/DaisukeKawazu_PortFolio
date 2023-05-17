#pragma once
#include "Component.h"


//•`‰æ‚·‚é‡˜‚Í’l‚Ì¬‚³‚¢‡‚Æ‚·‚éBŠî€‚Æ‚È‚é‡”Ô‚ÍA”wŒiAáŠQ•¨A“GAƒAƒCƒeƒ€A•—‘DAƒvƒŒƒCƒ„AIF
//‡”Ô‚Íã‹L‚Ì•`‰æ‘ÎÛ‚Ì¶‚©‚ç‚P‚O‚O‚¸‚Â‘‰Á‚³‚¹‚éB
//====================================--//
//”wŒiF‚P‚O‚O
//áŠQ•¨F‚Q‚O‚O
//“GF‚R‚O‚O
//ƒAƒCƒeƒ€F‚S‚O‚O
//•—‘DF‚T‚O‚O
//ƒvƒŒƒCƒ„F‚U‚O‚O
//IFF‚V‚O‚O
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
        void StaticDraw();//Update‚³‚ê‚È‚¢•`‰æ

        void SetTextureID(int tID) { TextureID = tID; }
        int GetDrawOrder() { return mDrawOrder; }

        virtual void UpdateDraw() {};
       // virtual void DrawEnemy() {}; g—p‚µ‚Ä‚¢‚È‚¢‚½‚ßíœ—\’è
        void AddAnim(class AnimationComponent* animcomp) { mAnimcomp = animcomp; }
    private:
        int TextureID;
        int mDrawOrder;
        class AnimationComponent* mAnimcomp;
       
};

