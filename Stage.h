#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class Stage :
    public GameObject
{
public:
    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    Fbx* pFbx_;
    int hModel_;
};

