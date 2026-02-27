#include "Ally.h"
#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "StageManager.h"
#include "Engine\\Command.h"

const float DELTA_TIME = 1.0f / 60.0f;

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr), moveSpeed_(0.5f),
	pTargetPlayer_(nullptr), gravity_(5.0f), velocityY_(0.0f), isOnGround_(false),
	maxHp_(50), currentHp_(50), attackPower_(20), defensePower_(10),
	pSM_(nullptr), currentScene_(SCENE_ID::SCENE_ID_PLAY), pCurrentCommand_(nullptr)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	hModel_ = Model::Load("Ally.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -5.0f, 5.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);

	SetAttackType(AttackType::BLUNT);
	SetDefenseType(DefenseType::NONE);
	SetElementType(ElementType::NONE);
	SetLevel(1);

	maxHp_ = 50;
	currentHp_ = maxHp_;
}

void Ally::Update()
{
	pSM_ = (SceneManager*)FindObject("SceneManager");
	SCENE_ID lastScene = currentScene_;
	currentScene_ = pSM_->GetCurrentSceneID();

	// シーン切り替え時にクリア
	if (lastScene != currentScene_)
	{
		posHistory_.clear();
	}

	if (currentHp_ <= 0)
	{
		this->KillMe();
		return;
	}

	ExecuteCommand();

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

		//for (auto stage : stages)
		//{
		//	if (CheckRayToWall({ nextX, transform_.position_.y, transform_.position_.z }, stage, true))
		//	{
		//		hit = true;
		//		break;
		//	}
		//}

		//if (!hit)
		//{
		//	transform_.position_.x = nextX;
		//}

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
		velocityY_ -= gravity_ * DELTA_TIME;
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
	//if (pTarget->GetName() == "Enemy")
	//{
	//	int damage = this->CalculateDamage(this->attackPower_, pTarget);

	//	pTarget->ApplyDamage(damage);
	//}
}

void Ally::ReceiveCommand(Command* pCommand)
{
	//if (pCurrentCommand_ != nullptr)
	//{
	//	delete pCurrentCommand_;
	//	pCurrentCommand_ = nullptr;
	//}
	pCurrentCommand_ = pCommand;
}

void Ally::ExecuteCommand()
{
	if (pCurrentCommand_ == nullptr) return;

	// 1. 対象（Enemy）を探す
	GameObject* pEnemy = FindObject("Enemy");
	if (pEnemy != nullptr)
	{
		// 2. コマンド実行（画像にある「行動」の部分）
		pCurrentCommand_->Execute(this, pEnemy);

		// 3. 実行が終わったので、自分を解放（画像にある「掃除」の部分）
		delete pCurrentCommand_;
		pCurrentCommand_ = nullptr;

		// デバッグログを出しておくと流れが追いやすくなります
		OutputDebugStringA("Command Executed and Deleted.\n");
	}
}

void Ally::UpdateMovement()
{
	pTargetPlayer_ = FindObject("Player");
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
		if (posHistory_.size() > FOLLOW_DELAY && !posHistory_.empty())
		{
			XMFLOAT3 targetPos = posHistory_.back();
			transform_.position_.x = targetPos.x;
			transform_.position_.z = targetPos.z;
			posHistory_.pop_back();
		}
	}	
	else
	{
		while (posHistory_.size() > FOLLOW_DELAY)
		{
			posHistory_.pop_back();
		}
	}
}

void Ally::UpdateBattle()
{
	pTargetPlayer_ = FindObject("Player");
	pTargetEnemy_ = FindObject("Enemy");
}
