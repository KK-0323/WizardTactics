#pragma once
#include "Engine\\GameObject.h"
#include <cmath>

class Fbx; // ‘O•ûéŒ¾

class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
    float gravity_;
    float moveSpeed_;
    float velocityY_;
    bool isOnGround_;
};

