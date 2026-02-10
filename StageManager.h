#pragma once
#include "Engine\\GameObject.h"

static const char* ModelType[] 
        = { "", "BoxGrass.fbx", "BoxWater.fbx", "BoxSand.fbx", "BoxBrick.fbx" };

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

