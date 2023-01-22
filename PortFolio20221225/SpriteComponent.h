#pragma once
#include "Component.h"

class SpriteComponent :
    public Component
{
    public:
        SpriteComponent(Actor* actor);
        ~SpriteComponent();
        void InitSprite(void);
        void UninitSprite(void);

        void DrawSprite(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteRotate(float x, float y, float width, float height, float u, float v, float uw, float vh, float rot);
        void DrawSpriteLeftTop(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteColor(float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a);
        
        void Draw(void);
        void SetTexture(int tex);
    private:
        int g_TextureNo;
        //class Actor* mOwner;

};

