#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), moveSpeed_(10.0f),
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false), maxMp_(100), currentMp_(100)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	isOnGround_ = false;

	// コマンドコスト
	const int NONE_COST = 0;
	const int ATTACK_COST = 0;
	const int DEFENSE_COST = 0;
	const int SKILL_COST = 20;

	// コマンドの指示入力
	if (Input::IsKeyDown(DIK_1))
	{
		IssueCommand(CMD_ATTACK, ATTACK_COST);
	}
	if (Input::IsKeyDown(DIK_2))
	{
		IssueCommand(CMD_DEFENSE, DEFENSE_COST);
	}
	if (Input::IsKeyDown(DIK_3))
	{
		IssueCommand(CMD_SKILL, SKILL_COST);
	}
	if (Input::IsKeyDown(DIK_0))
	{
		IssueCommand(CMD_NONE, NONE_COST);
	}

	// 移動処理
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= moveSpeed_ * DELTA_TIME;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += moveSpeed_ * DELTA_TIME;
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

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
	Model::Release();
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetName() == "Stage")
	{
		float stageY = pTarget->GetPosition().y;
		float stageScaleY = pTarget->GetScale().y;
		float stageHalfExtentY = 1.0f;

		float stageTopY = stageY + (stageHalfExtentY * stageScaleY);

		float playerRadius = 0.5f;

		float playerBottomY = transform_.position_.y - playerRadius;

		float overlap = stageTopY - playerBottomY;

		if (overlap > 0.0f)
		{
			transform_.position_.y += overlap;
			isOnGround_ = true;
			velocityY_ = 0.0f;
		}
	}
}

void Player::IssueCommand(AllyCommand command, int mpCost)
{
	if (currentMp_ >= mpCost)
	{
		currentMp_ -= mpCost;

		GameObject* pAllyObj = FindObject("Ally");
		if (pAllyObj != nullptr)
		{
			Ally* pAlly = dynamic_cast<Ally*>(pAllyObj);
			if (pAlly != nullptr)
			{
				pAlly->ReceiveCommand(command);
			}
		}
	}
	else
	{
		MessageBoxA(0, "MPが足りません！", "MP Lost", MB_OK);
	}
}
