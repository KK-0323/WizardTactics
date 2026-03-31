#include "Enemy.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "Engine\\SceneManager.h"
#include "StageManager.h"

const float DELTA_TIME = 1.0f / 60.0f;

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx_(nullptr),
	velocityY_(0.0f), isOnGround_(false)
{
}

Enemy::Enemy(GameObject* parent, ENEMY_ID id)
	:GameObject(parent, "Enemy"), pFbx_(nullptr), 
	velocityY_(0.0f), isOnGround_(false),enemyID_(id)
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
		transform_.position_ = { 10.0f, 5.0f, 0.0f };
		transform_.rotate_.y = 90.0f;
		initialX_ = transform_.position_.x;

		level_ = 1;
		maxHp_ = 30;
		currentHp_ = maxHp_;
		break;
	case ENEMY_BOSS:
		hModel_ = Model::Load("BossEnemy.fbx");
		assert(hModel_ >= 0);
		transform_.position_ = { 15.0f, 5.0f, 0.0f };
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
	bool hit = false;

	StageManager* pStageManager = (StageManager*)FindObject("StageManager");

	if (pStageManager != nullptr)
	{
		const auto& stages = pStageManager->GetStageList();

		XMFLOAT3 rayOrigin = transform_.position_;
		rayOrigin.y += 0.5f;

		// 床との当たり判定
		for (auto stage : stages)
		{
			if (CheckRayToStage(rayOrigin, stage))
			{
				float topY = stage->GetPosition().y + (stage->GetScale().y * 0.5f);
				float playerFeetY = transform_.position_.y - 0.5f;

				if (velocityY_ <= 0.0f)
				{
					hit = true;
					transform_.position_.y = topY + 0.5f;
					velocityY_ = 0.0f;
				}
				break;
			}
		}

		//天井との当たり判定
		if (velocityY_ > 0.0f)
		{
			for (auto stage : stages)
			{
				XMFLOAT3 headPos = transform_.position_;
				headPos.y += 0.4f;
				if (CheckRayToCelling(headPos, stage))
				{
					velocityY_ = 0.0f;

					float halfY = stage->GetScale().y * 0.5f;
					float bottomY = stage->GetPosition().y - halfY;
					transform_.position_.y = bottomY - 0.5f;
					break;
				}
			}
		}


	}

	isOnGround_ = hit;

	if (!isOnGround_)
	{
		velocityY_ -= GRAVITY * DELTA_TIME;
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

	if (pTarget->GetName() == "Ally")
	{
		int damage = pTarget->CalculateDamage(20, this);

		this->currentHp_ -= damage;

		if (this->currentHp_ <= 0)
		{
			this->currentHp_ = 0;

			GameObject* sceneObj = FindObject("SceneManager");
			if (sceneObj)
			{
				SceneManager* pSM = (SceneManager*)sceneObj;
				pSM->ChangeScene(SCENE_ID_CLEAR);
			}
			this->KillMe();
		}
	}
}