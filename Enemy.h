#pragma once
#include "Engine\\GameObject.h"

class Fbx;

enum ENEMY_ID
{
	ENEMY_ZAKO,
	ENEMY_BOSS,
	ENEMY_MAX
};

class Enemy :
    public GameObject
{
public:
	Enemy(GameObject* parent);
	Enemy(GameObject* parent, ENEMY_ID id);
	~Enemy();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* pTarget) override;

private:
	// メンバ変数
	Fbx* pFbx_;
	int hModel_;
	ENEMY_ID enemyID_;
	float velocityY_;
	bool isOnGround_;

	// 定数
	const float GRAVITY;

	// ステータス
	int level_;
	int maxHp_;
	int currentHp_;
};

