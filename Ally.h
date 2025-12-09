#pragma once
#include "Engine\\GameObject.h"
#include <cmath>

class Fbx;

// 受け取る指示の種類
enum AllyCommand
{
    CMD_NONE,
    CMD_ATTACK,
    CMD_DEFENSE,
    CMD_SKILL,
    CMD_ESCAPE,
    CMD_MAX
};

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
    void OnCollision(GameObject* pTarget) override;
    void ReceiveCommand(AllyCommand command);
private:
    Fbx* pFbx_;
    int hModel_;
    float moveSpeed_;
    float gravity_;
    float velocityY_;
    GameObject* pTargetPlayer_;
    bool isOnGround_;

	// ステータス用の変数
    int maxHp_;
    int currentHp_;
    int attackPower_;
    int defensePower_;

    // コマンド処理
    AllyCommand currentCommand_;
};

