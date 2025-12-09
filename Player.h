#pragma once
#include "Engine\\GameObject.h"
#include "Ally.h"
#include <cmath>

class Fbx; // 前方宣言

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
private:
    Fbx* pFbx_;
    int hModel_;
    float gravity_;
    float moveSpeed_;
    float velocityY_;
    bool isOnGround_;

    // ステータス用の変数
    int maxMp_;
    int currentMp_;

    // 指示コマンド用の関数
    void IssueCommand(AllyCommand command, int mpCost);
};

