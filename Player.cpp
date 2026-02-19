#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"
#include "Magic.h"

const float DELTA_TIME = 1.0f / 60.0f;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), moveSpeed_(10.0f),
	gravity_(5.0f), velocityY_(0.0f), isOnGround_(false), maxMp_(100), currentMp_(100),
	jumpCount_(0), isFloating_(false), floatTimer_(0.0f), pSM_(nullptr), currentScene_(SCENE_ID::SCENE_ID_PLAY)
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

	pAlly_ = (Ally*)FindObject("Ally");

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
	
	
	// 重力処理
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
	if (pTarget->GetName() == "Stage" || pTarget->GetName() == "BattleStage")
	{
		if (velocityY_ <= 0.0f)
		{
			float stageTopY = pTarget->GetPosition().y + (1.0f * pTarget->GetScale().y);
			float playerBottomY = transform_.position_.y - 0.5f;
			float overlap = stageTopY - playerBottomY;

			if (overlap > 0.0f)
			{
				transform_.position_.y += overlap;
				isOnGround_ = true;
				velocityY_ = 0.0f;
			}
		}
	}
}

void Player::IssueCommand(AllyCommand command, int mpCost)
{
	if (currentMp_ >= mpCost)
	{
		currentMp_ -= mpCost;

		if (pAlly_ != nullptr)
		{
			pAlly_->ReceiveCommand(command);
		}
	}
	else
	{
		MessageBoxA(0, "MPが足りません！", "MP Lost", MB_OK);
	}
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
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += currentMoveSpeed_ * DELTA_TIME;
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

void Player::UpdateBattle()
{
	// コマンドの指示入力
	if (Input::IsKeyDown(DIK_1))
	{
		IssueCommand(CMD_ATTACK, ATTACK_COST);
		MessageBoxA(0, "攻撃", "ATTACK", MB_OK);
	}
	if (Input::IsKeyDown(DIK_2))
	{
		IssueCommand(CMD_DEFENSE, DEFENSE_COST);
		MessageBoxA(0, "防御", "DEFENSE", MB_OK);
	}
	if (Input::IsKeyDown(DIK_3))
	{
		IssueCommand(CMD_SKILL, SKILL_COST);
		MessageBoxA(0, "特技", "SKILL", MB_OK);
	}
	if (Input::IsKeyDown(DIK_4))
	{
		IssueCommand(CMD_NONE, NONE_COST);
		MessageBoxA(0, "待機", "NONE", MB_OK);
	}
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
