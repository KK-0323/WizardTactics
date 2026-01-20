#include "Enemy.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "Engine\\SceneManager.h"

const float DELTA_TIME = 1.0f / 60.0f;

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx_(nullptr),
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false)
{
}

Enemy::Enemy(GameObject* parent, ENEMY_ID id)
	:GameObject(parent, "Enemy"), pFbx_(nullptr), 
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false),
	enemyID_(id)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	switch (enemyID_)
	{
	case ENEMY_ZAKO:
		hModel_ = Model::Load("Enemy.fbx");
		assert(hModel_ >= 0);
		transform_.position_ = { 10.0f, 0.0f, 0.0f };
		transform_.rotate_.y = 90.0f;
		initialX_ = transform_.position_.x;

		level_ = 1;
		maxHp_ = 30;
		currentHp_ = maxHp_;
		break;
	case ENEMY_BOSS:
		hModel_ = Model::Load("BossEnemy.fbx");
		assert(hModel_ >= 0);
		transform_.position_ = { 20.0f, 0.0f, 0.0f };
		transform_.rotate_.y = 90.0f;
		level_ = 10;
		maxHp_ = 200;
		currentHp_ = maxHp_;
		break;
	case ENEMY_MAX:
		break;
	default:
		break;
	}
	SetLevel(level_);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Enemy::Update()
{
	//time_ += DELTA_TIME;

	//float offsetX = amplitude_ * std::sin(moveSpeed_ * time_);

	//transform_.position_.x = initialX_ + offsetX;

	if (!isOnGround_)
	{
		velocityY_ -= gravity_ * DELTA_TIME;
	}
	else
	{
		velocityY_ = 0.0f;
	}
	// Y座標に速度を適用
	transform_.position_.y += velocityY_ * DELTA_TIME;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetName() == "Player")
	{
		GameObject* sceneObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_BATTLE);
			}
		}
	}

	if (pTarget->GetName() == "Stage")
	{
		float stageY = pTarget->GetPosition().y;
		float stageScaleY = pTarget->GetScale().y;
		float stageHalfExtentY = 1.0f;

		float stageTopY = stageY + (stageHalfExtentY * stageScaleY);

		float enemyRadius = 0.5f;

		float enemyBottomY = transform_.position_.y - enemyRadius;

		float overlap = stageTopY - enemyBottomY;

		if (overlap > 0.0f)
		{
			transform_.position_.y += overlap;
			isOnGround_ = true;
			velocityY_ = 0.0f;
		}
	}
	if (pTarget->GetName() == "BattleStage")
	{
		float stageY = pTarget->GetPosition().y;
		float stageScaleY = pTarget->GetScale().y;
		float stageHalfExtentY = 1.0f;

		float stageTopY = stageY + (stageHalfExtentY * stageScaleY);

		float enemyRadius = 0.5f;

		float enemyBottomY = transform_.position_.y - enemyRadius;

		float overlap = stageTopY - enemyBottomY;

		if (overlap > 0.0f)
		{
			transform_.position_.y += overlap;
			isOnGround_ = true;
			velocityY_ = 0.0f;
		}
	}
	if (pTarget->GetName() == "Magic")
	{
		KillMe();
		pTarget->KillMe();

		GameObject* sceneObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_TITLE);
			}
		}
	}
}