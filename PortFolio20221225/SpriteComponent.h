#pragma once
#include "Component.h"

class SpriteComponent :
    public Component
{
    public:
        SpriteComponent(class Actor* Owner, class Player* Player);
        SpriteComponent(Actor* actor);
        ~SpriteComponent();
        void InitSprite(void);
        void UninitSprite(void);

        void DrawSprite(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteRotate(float x, float y, float width, float height, float u, float v, float uw, float vh, float rot);
        void DrawSpriteLeftTop(float x, float y, float width, float height, float u, float v, float uw, float vh);
        void DrawSpriteColor(float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a);
        
        virtual void Draw();
        void SetTextureID(int tID) { TextureID = tID; }
    
    private:
        int TextureID;
       
};

