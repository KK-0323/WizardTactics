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
	transform_.position_ = { -5.0f, 0.0f, 0.0f };
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
	if (pTarget->GetName() == "BattleStage")
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

	if (pTarget->GetName() == "Enemy")
	{
		int damage = this->CalculateDamage(this->attackPower_, pTarget);

		pTarget->ApplyDamage(damage);
	}
}

void Ally::ReceiveCommand(AllyCommand command)
{
	pTargetPlayer_ = FindObject("Player");
	if (!pTargetPlayer_)
	{
		return;
	}

	if (pTargetPlayer_->GetLevel() >= this->GetLevel())
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
	else
	{
		state_ = AllyState::RANDOM;
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

	AllyState executeState = state_;

	if (executeState == AllyState::RANDOM)
	{
		int dice = rand() % 3;
		if (dice == 0)
		{
			executeState = AllyState::ATTACK;
		}
		else if (dice == 1)
		{
			executeState = AllyState::DEFENSE;
		}
		else
		{
			executeState = AllyState::SKILL;
		}
		
		MessageBoxA(NULL, "ランダム行動", "反抗", MB_OK);
	}
	
	switch (executeState)
	{
	case AllyState::IDLE:
		break;
	case AllyState::ATTACK:
		if (pTargetEnemy_->GetPosition().x - 1.0f < transform_.position_.x)
		{
			transform_.position_.x += moveSpeed_ * DELTA_TIME;
			int damage = this->CalculateDamage(this->attackPower_, pTargetEnemy_);
			pTargetEnemy_->ApplyDamage(damage);
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
