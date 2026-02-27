#pragma once
#include "Engine\\GameObject.h"
#include <cmath>
#include "Engine\\SceneManager.h"
//#include "Weapon.h"

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

    bool isMovingL_;
    bool isMovingR_;
    int jumpCount_;
    const int MAX_JUMP = 2;
    bool isFloating_;
    float floatTimer_;
    const float MAX_FLOAT_TIME = 5.0f;

    // コマンドコスト
    const int NONE_COST = 0;
    const int ATTACK_COST = 0;
    const int DEFENSE_COST = 0;
    const int SKILL_COST = 20;

    SceneManager* pSM_;
    SCENE_ID currentScene_;

    void UpdateMovement();
    void UpdateBattle();

    //Weapon::WeaponType currentWeapon_ = Weapon::STAFF;

    enum class BattleState
    {
        SELECT_COMMAND,
        WAIT_ACTION,
        STATE_MAX
    };
    BattleState bState_ = BattleState::SELECT_COMMAND;
};