#pragma once
#include "Engine\\GameObject.h"
#include <cmath>

class Fbx;

class Enemy :
    public GameObject
{
public:
	Enemy(GameObject* parent);
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* pTarget) override;
private:
	Fbx* pFbx_;
	int hModel_;

	// 往復運動(仮)
	float initialX_ = 0.0f;
	float amplitude_ = 5.0f;
	float moveSpeed_ = 5.0f;
	float time_ = 0.0f;

	// ステージとの当たり判定用
	float gravity_;
	float velocityY_;
	bool isOnGround_;
};

