#pragma once
#include "Engine\\GameObject.h"
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
    CommandType currentCommand_ = CommandType::NONE;
};

