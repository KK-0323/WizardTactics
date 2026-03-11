#include "Ally.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "StageManager.h"
#include "Player.h"
#include "Engine\\Command.h"

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
	//if (curHp_ <= 0)
	//{
	//	this->KillMe();
	//	return;
	//}

	UpdateMovement();

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

	GameObject* pObj = FindObject("Player");
	char buf[128];
	sprintf_s(buf, "Ally Sees : %p, ActualPlayerX: %f\n", pObj, pObj->GetPosition().x);
	OutputDebugStringA(buf);

	Player* pPlayer = static_cast<Player*>(pObj);
	OrderData data = pPlayer->GetOrder();
	//if (data.type_ == CommandType::ATTACK)
	//{
	//	OutputDebugStringA("攻撃指示を受信しましたよ！\n");
	//}

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
	//if (pTarget->GetName() == "Enemy")
	//{
	//	int damage = this->CalculateDamage(this->attackPower_, pTarget);
	//	pTarget->ApplyDamage(damage);
	//}
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
		if (posHistory_.size() > 20 && !posHistory_.empty())
		{
			XMFLOAT3 targetPos = posHistory_.back();
			transform_.position_.x = targetPos.x;
			transform_.position_.z = targetPos.z;
			posHistory_.pop_back();
		}
	}	
	//else
	//{
	//	while (posHistory_.size() > FOLLOW_DELAY)
	//	{
	//		posHistory_.pop_back();
	//	}
	//}
}