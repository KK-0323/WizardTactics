#include "Ally.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "StageManager.h"
#include "Engine\\Input.h"

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr),
	maxHp_(50), curHp_(50), atkPower_(20), defPower_(20),
	velocityY_(0.0f), isOnGround_(false)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	hModel_ = Model::Load("Ally.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -2.0f, 5.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Ally::Update()
{
	pSM_ = (SceneManager*)FindObject("SceneManager");
	SCENE_ID lastScene = currentScene_;
	currentScene_ = pSM_->GetCurrentSceneID();

	
		
	switch (currentScene_)
	{
	case SCENE_ID_PLAY:
		UpdateMovement();
		break;
	case SCENE_ID_BATTLE:
		UpdateBattle();
		break;
	default:
		break;
	}

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

void Ally::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ally::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void Ally::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetName() == "Enemy")
	{
		int damage = this->CalculateDamage(this->atkPower_, pTarget);
		pTarget->ApplyDamage(damage);
	}
}

void Ally::UpdateMovement()
{
	GameObject* pTargetPlayer_ = FindObject("Player");
	if (!pTargetPlayer_)
	{
		return;
	}

	XMFLOAT3 playerPos = pTargetPlayer_->GetPosition();
	if (posHistory_.empty())
	{
		posHistory_.push_front(playerPos);
	}
	else
	{
		XMVECTOR p1 = XMLoadFloat3(&playerPos);
		XMVECTOR p2 = XMLoadFloat3(&posHistory_.front());
		float dist = XMVectorGetX(XMVector3Length(p1 - p2));

		if (dist > 0.1f)
		{
			posHistory_.push_front(playerPos);
		}
	}

	XMVECTOR myPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR pPos = XMLoadFloat3(&playerPos);
	float distanceToPlayer = XMVectorGetX(XMVector3Length(pPos - myPos));
	
	const float STOP_DISTANCE = 2.0f;
	if (distanceToPlayer > STOP_DISTANCE)
	{
		if (posHistory_.size() > FOLOOW_SPEED && !posHistory_.empty())
		{
			XMFLOAT3 targetPos = posHistory_.back();
			transform_.position_.x = targetPos.x;
			transform_.position_.z = targetPos.z;
			posHistory_.pop_back();
		}
	}	
	else
	{
		while (posHistory_.size() > FOLOOW_SPEED)
		{
			posHistory_.pop_back();
		}
	}
}

void Ally::UpdateBattle()
{
	if (Input::IsKeyDown(DIK_1))
	{
		cType_ = CommandType::ATTACK;
	}
	else if (Input::IsKeyDown(DIK_0))
	{
		cType_ = CommandType::NONE;
	}


	if (cType_ == CommandType::ATTACK && transform_.position_.x <= ATTACK_POSITION)
	{
		transform_.position_.x += 0.5f;
		transform_.rotate_.y += 10.0f;
	}
	if (cType_ == CommandType::NONE)
	{
		transform_.position_.x = START_POSTION;
		transform_.rotate_.y = 90.0f;
	}
}
