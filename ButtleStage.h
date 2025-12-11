#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class ButtleStage :
    public GameObject
{
public:
    ButtleStage(GameObject* parent);
    ~ButtleStage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
};

