#pragma once
#include "Engine\\GameObject.h"

class BattleStage :
    public GameObject
{
public:
    BattleStage(GameObject* parent, std::string modelPath);
    ~BattleStage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    std::string modelPath_;
    int hModel_;
};

