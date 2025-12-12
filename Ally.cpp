#include "Ally.h"
#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr), moveSpeed_(0.5f),
	pTargetPlayer_(nullptr), gravity_(5.0f), velocityY_(0.0f), isOnGround_(false),
	maxHp_(50), currentHp_(50), attackPower_(20), defensePower_(10),
	currentCommand_(CMD_NONE)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	hModel_ = Model::Load("Ally.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Ally::Update()
{
	// ポインタ取得
	pTargetPlayer_ = FindObject("Player");
	switch (currentCommand_)
	{
	case CMD_NONE:
		// Playerの位置に合わせて追従
		if (pTargetPlayer_)
		{
			const XMFLOAT3& playerPos = pTargetPlayer_->GetPosition();

			XMFLOAT3 targetPos = playerPos;

			transform_.position_.x = targetPos.x - 3.0f;
		}
		break;
	case CMD_ATTACK:
		break;
	case CMD_DEFENSE:
		break;
	case CMD_SKILL:
		break;
	case CMD_ESCAPE:
		break;
	case CMD_MAX:
		break;
	default:
		break;
	}


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
	if (pTarget->GetName() == "Stage")
	{
		float stageY = pTarget->GetPosition().y;
		float stageScaleY = pTarget->GetScale().y;
		float stageHalfExtentY = 1.0f;

		float stageTopY = stageY + (stageHalfExtentY * stageScaleY);

		float allyRadius = 0.5f;

		float allyBottomY = transform_.position_.y - allyRadius;

		float overlap = stageTopY - allyBottomY;

		if (overlap > 0.0f)
		{
			transform_.position_.y += overlap;
			isOnGround_ = true;
			velocityY_ = 0.0f;
		}
	}
	else if (pTarget->GetName() == "ButtleStage")
	{
		float stageY = pTarget->GetPosition().y;
		float stageScaleY = pTarget->GetScale().y;
		float stageHalfExtentY = 1.0f;

		float stageTopY = stageY + (stageHalfExtentY * stageScaleY);

		float allyRadius = 0.5f;

		float allyBottomY = transform_.position_.y - allyRadius;

		float overlap = stageTopY - allyBottomY;

		if (overlap > 0.0f)
		{
			transform_.position_.y += overlap;
			isOnGround_ = true;
			velocityY_ = 0.0f;
		}
	}
}

void Ally::ReceiveCommand(AllyCommand command)
{
	currentCommand_ = command;
}
