#pragma once
#include "Engine\\GameObject.h"
#include <cmath>
#include <deque>
#include "Engine\\SceneManager.h"

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

enum AllyState
{
    IDLE,
    ATTACK,
    DEFENSE,
    SKILL,
    ESCAPE,
    RANDOM,
    MAX
};

struct Skill
{
    std::string name;
    int mpCost;
    int power;
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
    GameObject* pTargetEnemy_;
    bool isOnGround_;

	// ステータス用の変数
    int maxHp_;
    int currentHp_;
    int attackPower_;
    int defensePower_;

    std::deque<XMFLOAT3> posHistory_; // プレイヤー座標履歴
    const int FOLLOW_DELAY = 40;
    SceneManager* pSM_;
    SCENE_ID currentScene_;

    AllyCommand currentCommand_;

    void UpdateMovement();
    void UpdateBattle();

    AllyState state_;
};

