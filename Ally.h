#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\Fbx.h"

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
    float moveSpeed__;
    GameObject* pTargetPlayer_;
};

