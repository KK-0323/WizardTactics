#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class TestEnemy :
    public GameObject
{
public:
    TestEnemy(GameObject* parent);
    ~TestEnemy();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
};

