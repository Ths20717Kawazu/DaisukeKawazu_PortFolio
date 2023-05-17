#pragma once
#include "Component.h"


//�`�悷�鏇���͒l�̏��������Ƃ���B��ƂȂ鏇�Ԃ́A�w�i�A��Q���A�G�A�A�C�e���A���D�A�v���C���AIF
//���Ԃ͏�L�̕`��Ώۂ̍�����P�O�O������������B
//====================================--//
//�w�i�F�P�O�O
//��Q���F�Q�O�O
//�G�F�R�O�O
//�A�C�e���F�S�O�O
//���D�F�T�O�O
//�v���C���F�U�O�O
//IF�F�V�O�O
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
        void StaticDraw();//Update����Ȃ��`��

        void SetTextureID(int tID) { TextureID = tID; }
        int GetDrawOrder() { return mDrawOrder; }

        virtual void UpdateDraw() {};
       // virtual void DrawEnemy() {}; �g�p���Ă��Ȃ����ߍ폜�\��
        void AddAnim(class AnimationComponent* animcomp) { mAnimcomp = animcomp; }
    private:
        int TextureID;
        int mDrawOrder;
        class AnimationComponent* mAnimcomp;
       
};

