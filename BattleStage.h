#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class BattleStage :
    public GameObject
{
public:
    BattleStage(GameObject* parent);
    ~BattleStage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
};

