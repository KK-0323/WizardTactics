#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\SceneManager.h"
#include "CommandType.h"
#include <deque>
#include <DirectXMath.h>

// 前方宣言
class Fbx;
class StageManager;

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

private:
    void UpdateMovement(); // 移動
    void UpdateBattle();   // 戦闘

    // メンバ変数
    Fbx* pFbx_;
    int hModel_;
    
    // 移動関連
    float velocityY_;
    bool isOnGround_;

	// ステータス
    int maxHp_;
    int curHp_;
    int atkPower_;
    int defPower_;
    
    // 定数
    const float FOLOOW_SPEED = 0.5f;
    const float MIN_FOLLOW_DIST = 0.1f;
    const float GRAVITY = 5.0f;
    const float DELTA_TIME = 1.0f / 60.0f;
    const float START_POSTION = -2.0f;
    const float ATTACK_POSITION = 10.0f;

    // 追従
    std::deque<XMFLOAT3> posHistory_; // 座標履歴

    // 参照
    SceneManager* pSM_ = nullptr;
    SCENE_ID currentScene_ = SCENE_ID_PLAY;
    CommandType cType_ = CommandType::NONE;
};

