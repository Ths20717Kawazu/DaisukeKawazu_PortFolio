#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{

public:
    enum EnemyState {
        IDLE,
        WALK,
        RUN

    };
    Enemy(class Game* game, enum Actor::Tag tag);
    ~Enemy();//�p����̃f�X�g���N�^���@�\�����邽�߂�Virtual�͖Y��Ȃ�����
    void UpdateActor() override;
    void Damage(int damage) override;
    void AddImage(int img, Enemy::EnemyState state);
    void AddAnimOrders(int order, Enemy::EnemyState state);
    //�h���N���X�̉摜�z����擾����B
    std::vector<int> GetAnimImages(Enemy::EnemyState state);
    std::vector<int> GetAnimOrders(Enemy::EnemyState state);


    enum EnemyState SetState(enum EnemyState state) { mState = state; }
    enum EnemyState GetState() { return mState; }

    int getWidth() { return EnemyWidth;}
    int getHeight() { return EnemyHeight; }

    void SetVel(float x, float y) { mVel.x = x, mVel.y = y;  }


private:
    int EnemyWidth = 100;
    int EnemyHeight = 100;
    D3DXVECTOR2 mVel{0.0f, 0.0f};
    enum EnemyState mState;
    //�摜�z��
    std::vector<int>mIdleImages;
    std::vector<int>mWalkImages; 
    //�摜�\������
    std::vector<int>animIdleOrders;
    

};

