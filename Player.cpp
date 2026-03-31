#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"
#include "StageManager.h"
#include "Magic.h"
#include "Ally.h"
#include "Engine\\Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr),isOnGround_(false),
	maxHp_(100), currentHp_(100), maxMp_(100), currentMp_(100),
	floatTimer_(0.0f), velocityY_(0.0f), jumpCount_(0), isFloating_(false),
	isMovingL_(false), isMovingR_(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Earth.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, 5.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	pSM_ = (SceneManager*)FindObject("SceneManager");
	SCENE_ID lastScene = currentScene_;
	currentScene_ = pSM_->GetCurrentSceneID();

	switch (currentScene_)
	{
	case SCENE_ID_PLAY:
		UpdateMovement();
		UpdateFloating();
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
					jumpCount_ = 0;
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
	
	// 重力処理
	if (!isOnGround_)
	{
		velocityY_ -= GRAVITY * DELTA_TIME;
	}
	
	// Y座標に速度を適用
	transform_.position_.y += velocityY_ * DELTA_TIME;

	// カメラ処理
	XMFLOAT3 camPos = transform_.position_;
	if (pParent_->GetName() == "PlayScene")
	{
		camPos.y += 10.0f;
		camPos.z -= 30.0f;
		Camera::SetPosition(XMLoadFloat3(&camPos));
		Camera::SetTarget(XMLoadFloat3(&transform_.position_));
	}
	else
	{
		Camera::SetPosition(XMVectorSet(0, 20.0f, -50.0f, 0));
		Camera::SetTarget(XMVectorSet(0, 0, 0, 0));
	}
}

// PlaySceneの処理
void Player::UpdateMovement()
{
	// 移動処理
	float currentMoveSpeed_ = MOVE_SPEED;
	isMovingL_ = false;
	isMovingR_ = false;

	// ジャンプ回数リセット
	if (isOnGround_)
	{
		jumpCount_ = 0;
	}

	if (Input::IsKey(DIK_LSHIFT))
	{
		currentMoveSpeed_ *= 2.0f;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= currentMoveSpeed_ * DELTA_TIME;
		isMovingL_ = true;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += currentMoveSpeed_ * DELTA_TIME;
		isMovingR_ = true;
	}
	if (Input::IsKeyDown(DIK_SPACE) && jumpCount_ < MAX_JUMP_COUNT)
	{
		velocityY_ = 5.0f;
		jumpCount_++;
		isOnGround_ = false;
	}
	
	if (!isFloating_ && !isOnGround_)
	{
		velocityY_ -= GRAVITY * DELTA_TIME;
	}

	transform_.position_.y += velocityY_ * DELTA_TIME;
}

// BattleSceneの処理
void Player::UpdateBattle()
{
	if (Input::IsKeyDown(DIK_1))
	{
		currentOrder_.type_ = CommandType::ATTACK;
		MessageBox(nullptr, L"攻撃を指示", L"attack", MB_OK);
	}
}

void Player::UpdateFloating()
{
	// 浮遊処理
	if (!isOnGround_ && jumpCount_ >= 1 && Input::IsKeyDown(DIK_C))
	{
		isFloating_ = true;
		floatTimer_ = MAX_FLOAT_TIME;
	}

	if (isFloating_)
	{
		floatTimer_ -= DELTA_TIME;
		velocityY_ = 0.0f;
		transform_.rotate_.y += 5.0f;

		if (floatTimer_ <= 0.0f || Input::IsKeyDown(DIK_S))
		{
			isFloating_ = false;
			transform_.rotate_.y = 90.0f;
		}

		if (Input::IsKey(DIK_SPACE))
		{
			velocityY_ = 2.0f;
		}
	}
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
}
