#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\Fbx.h"

class Ally :
    public GameObject
{
public:
    Ally(GameObject* parent);
    ~Ally();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Fbx* pFbx_;
};

