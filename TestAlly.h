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

private:
    Fbx* pFbx_;
    int hModel_;
};

