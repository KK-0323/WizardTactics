#pragma once
#include "Engine\\GameObject.h"

class Fbx;

class TestPlayer :
    public GameObject
{
public:
    TestPlayer(GameObject* parent);
    ~TestPlayer();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;

    // 参照データ
    CommandType GetCurrentCommand() const { return currentCommand_; }

private:
    Fbx* pFbx_;
    int hModel_;
    CommandType currentCommand_ = CommandType::NONE;
};

