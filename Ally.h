#pragma once
#include "Engine\\GameObject.h"
#include <cmath>

class Fbx;

class Ally :
    public GameObject
{
public:
    Ally(GameObject* parent);
    ~Ally();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
    float moveSpeed_;
    float gravity_;
    float velocityY_;
    GameObject* pTargetPlayer_;
    bool isOnGround_;
};

