#pragma once
#include "Engine\\GameObject.h"

class StageManager :
    public GameObject
{
public:
    StageManager(GameObject* parent);
    ~StageManager();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

