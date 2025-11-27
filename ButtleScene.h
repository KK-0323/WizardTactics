#pragma once
#include "Engine\\GameObject.h"
class ButtleScene :
    public GameObject
{
public:
    ButtleScene(GameObject* parent);
    ~ButtleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

