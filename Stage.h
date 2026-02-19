#pragma once
#include "Engine\\GameObject.h"

class Stage :
    public GameObject
{
public:
    Stage(GameObject* parent, std::string modelPath);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
private:
    std::string modelPath_;
    int hModel_;
};

