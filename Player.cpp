#include "Player.h"
#include "Engine\\Fbx.h"
#include "Engine\\Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), moveSpeed(0.5f)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Player.fbx");
	transform_.position_ = { -10.0f, 0.0f, 30.0f };
	transform_.rotate_.y = 90.0f;
}

void Player::Update()
{
	if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
	{
		transform_.position_.x -= moveSpeed;
	}
	if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
	{
		transform_.position_.x += moveSpeed;
	}
}

void Player::Draw()
{
	if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void Player::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}