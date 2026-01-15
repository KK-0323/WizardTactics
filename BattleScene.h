#pragma once
#include "Engine\\GameObject.h"
class BattleScene :
    public GameObject
{
public:
    BattleScene(GameObject* parent);
    ~BattleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

