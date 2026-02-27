#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\SceneManager.h"

// 前方宣言
class Fbx;
class Ally;

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
    void UpdateMovement();  // 移動
    void UpdateBattle();    // 戦闘
    void UpdateFloating();  // 浮遊

    // メンバ変数
    Fbx* pFbx_;
    int hModel_;

    // 移動関連
    int jumpCount_;
    float velocityY_;
    float floatTimer_;
    bool isOnGround_;
    bool isFloating_;
    bool isMovingL_;
    bool isMovingR_;

    // ステータス
    int maxHp_;
    int currentHp_;
    int maxMp_;
    int currentMp_;
    
    // 定数
    const float MOVE_SPEED = 10.0f;
    const float GRAVITY = 5.0f;
    const float JUMP_POWER = 5.0f;
    const int   MAX_JUMP_COUNT = 2;
    const float MAX_FLOAT_TIME = 3.0f;
    const int   SKILL_COST = 20;
    const float DELTA_TIME = 1.0f / 60.0f;
    

    // 参照
    SceneManager* pSM_ = nullptr;
    SCENE_ID currentScene_ = SCENE_ID_PLAY;
};