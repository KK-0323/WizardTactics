#pragma once
#include "Engine\\GameObject.h"
#include "Ally.h"
#include <cmath>

class Fbx; // 前方宣言

enum class PlayMode
{
    EXPLORE,
    BATTLE
};

class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
    void SetMode(PlayMode mode) { currentMode_ = mode; }
private:
    Fbx* pFbx_;
    int hModel_;
    float gravity_;
    float moveSpeed_;
    float velocityY_;
    bool isOnGround_;
    PlayMode currentMode_ = PlayMode::EXPLORE;

    // ステータス用の変数
    int maxMp_;
    int currentMp_;

    int jumpCount_;
    const int MAX_JUMP = 2;
    bool isFloating_;
    float floatTimer_;
    const float MAX_FLOAT_TIME = 5.0f;

    // 指示コマンド用の関数
    void IssueCommand(AllyCommand command, int mpCost);
    // コマンドコスト
    const int NONE_COST = 0;
    const int ATTACK_COST = 0;
    const int DEFENSE_COST = 0;
    const int SKILL_COST = 20;
};

