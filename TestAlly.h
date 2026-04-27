#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class TestAlly :
    public GameObject
{
public:
    TestAlly(GameObject* parent);
    ~TestAlly();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;

    void SetTargetEnemy(GameObject* pEnemy) { pEnemy_ = pEnemy; }

private:
    Fbx* pFbx_;
    int hModel_;
    GameObject* pPlayer_;
    GameObject* pEnemy_;
    CommandType currentCommand_ = CommandType::NONE;

    void CommandPattern();
};

