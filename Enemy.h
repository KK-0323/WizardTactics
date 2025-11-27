#pragma once
#include "Engine\\GameObject.h"
#include "Engine\\Fbx.h"
#include <cmath>

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

	float initialX_;
	float amplitude_ = 5.0f;
	float speed_ = 1.0f;

	float time_ = 0.0f;
};

