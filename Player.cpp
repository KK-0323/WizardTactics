#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), moveSpeed_(10.0f),
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -10.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
	{
		transform_.position_.x -= moveSpeed_ * DELTA_TIME;
	}
	if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
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
	isOnGround_ = false;
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
		velocityY_ = 0.0f;
		isOnGround_ = true;

		float stageY = pTarget->GetPosition().y;
		float stageHalfHeight = 0.5f;
		float stageTopY = stageY + stageHalfHeight;

		float playerRadius = 0.5f;
		transform_.position_.y = stageTopY + playerRadius;
	}
}