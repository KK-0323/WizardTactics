#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\Camera.h"
#include "Engine\\SphereCollider.h"
#include "Engine\\BoxCollider.h"
#include "Magic.h"
#include "Ally.h"
#include "StageManager.h"
#include "AtkCmd.h"

const float DELTA_TIME = 1.0f / 60.0f;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), moveSpeed_(10.0f),
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false), maxMp_(100), currentMp_(100), isMovingL_(false), isMovingR_(false),
	velocityY_(0.0f), jumpCount_(0), isFloating_(false)
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

	//SphereCollider* col = new SphereCollider(0.5f);
	BoxCollider* box = new BoxCollider({ 1.0f, 1.0f, 1.0f });
	AddCollider(box);

	//switch (currentWeapon_)
	//{
	//case Weapon::NONE:
	//	break;
	//case Weapon::SWORD:
	//	break;
	//case Weapon::FIST:
	//	break;
	//case Weapon::STAFF:
	//	SetAttackType(AttackType::MAGIC);
	//	SetDefenseType(DefenseType::NONE);
	//	SetElementType(ElementType::NONE);
	//	break;
	//case Weapon::MAX:
	//	break;
	//default:
	//	break;
	//}
	SetAttackType(AttackType::MAGIC);
	SetDefenseType(DefenseType::NONE);
	SetElementType(ElementType::NONE);
	SetLevel(1);
}

void Player::Update()
{
	pSM_ = (SceneManager*)FindObject("SceneManager");
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

	//float nextX = transform_.position_.x;
	//if (Input::IsKey(DIK_D)) nextX += moveSpeed_ * DELTA_TIME;
	//if (Input::IsKey(DIK_A)) nextX -= moveSpeed_ * DELTA_TIME;

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
		velocityY_ -= gravity_ * DELTA_TIME;
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

// PlaySceneの処理
void Player::UpdateMovement()
{
	// 移動処理
	float currentMoveSpeed_ = moveSpeed_;

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
	if (Input::IsKeyDown(DIK_SPACE))
	{
		if (jumpCount_ < MAX_JUMP)
		{
			velocityY_ = 5.0f;
			jumpCount_++;
			isOnGround_ = false;
		}
	}

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

		if (floatTimer_ <= 0.0f)
		{
			isFloating_ = false;
			transform_.rotate_.y = 90.0f;
		}
		else if (Input::IsKeyDown(DIK_S))
		{
			isFloating_ = false;
			transform_.rotate_.y = 90.0f;
		}

		if (Input::IsKey(DIK_SPACE))
		{
			velocityY_ = 2.0f;
		}
	}
	else if (!isOnGround_)
	{
		velocityY_ -= gravity_ * DELTA_TIME;
	}

	transform_.position_.y += velocityY_ * DELTA_TIME;
}

// BattleSceneの処理
void Player::UpdateBattle()
{
	if (Input::IsKeyDown(DIK_1))
	{
		// 1. コマンドを生成
		AtkCmd* pAtk = new AtkCmd();

		// 2. その場でAllyを探して渡す（メンバ変数のpAlly_が壊れていても安全）
		Ally* pTargetAlly = (Ally*)FindObject("Ally");
		if (pTargetAlly != nullptr)
		{
			pTargetAlly->ReceiveCommand(pAtk);
		}
		else
		{
			// Allyがいないなら、作ったコマンドを自分で消してメモリリークを防ぐ
			delete pAtk;
		}
	}


	// 
	// 魔法(仮)の生成
	if (Input::IsMouseButtonDown(0))
	{
		Magic* pMagic = Instantiate<Magic>(GetRootJob(), MAGIC_FIRE);
		if (pMagic != nullptr)
		{
			pMagic->SetPosition(transform_.position_);
		}
	}
}
