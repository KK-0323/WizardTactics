#include "Ally.h"
#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr), moveSpeed_(0.5f),
	pTargetPlayer_(nullptr), gravity_(5.0f), velocityY_(0.0f), isOnGround_(false),
	maxHp_(50), currentHp_(50), attackPower_(20), defensePower_(10),
	pSM_(nullptr), currentScene_(SCENE_ID::SCENE_ID_PLAY)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	hModel_ = Model::Load("Ally.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -3.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);

	SetAttackType(AttackType::BLUNT);
	SetDefenseType(DefenseType::NONE);
	SetElementType(ElementType::NONE);
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
	else if (pTarget->GetName() == "BattleStage")
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
	switch (command)
	{
	case CMD_NONE:
		state_ = AllyState::IDLE;
		break;
	case CMD_ATTACK:
		state_ = AllyState::ATTACK;
		break;
	case CMD_DEFENSE:
		state_ = AllyState::DEFENSE;
		break;
	case CMD_SKILL:
		state_ = AllyState::SKILL;
		break;
	case CMD_ESCAPE:
		state_ = AllyState::ESCAPE;
		break;
	case CMD_MAX:
		state_ = AllyState::MAX;
		break;
	default:
		break;
	}
}

void Ally::UpdateMovement()
{
	pTargetPlayer_ = FindObject("Player");
	if (!pTargetPlayer_)
	{
		return;
	}

	posHistory_.push_front(pTargetPlayer_->GetPosition());

	if (posHistory_.size() > FOLLOW_DELAY)
	{
		XMFLOAT3 targetPos = posHistory_.back();
		posHistory_.pop_back();

		transform_.position_.x = targetPos.x - 3.0f;
	}
}

void Ally::UpdateBattle()
{
	pTargetPlayer_ = FindObject("Player");
	pTargetEnemy_ = FindObject("Enemy");
	
	switch (state_)
	{
	case AllyState::IDLE:
		if (pTargetPlayer_)
		{
			transform_.position_.x = pTargetPlayer_->GetPosition().x - 3.0f;
		}
		break;
	case AllyState::ATTACK:
		if(transform_.position_.x < pTargetEnemy_->GetPosition().x - 1.0f)
		{
			transform_.position_.x += moveSpeed_ * DELTA_TIME * 60.0f;
		}
		break;
	case AllyState::DEFENSE:
		break;
	case AllyState::SKILL:
		break;
	case AllyState::ESCAPE:
		break;
	case AllyState::MAX:
		break;
	default:
		break;
	}
}
