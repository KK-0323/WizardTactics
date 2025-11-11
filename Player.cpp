#include "Player.h"
#include "Engine\\Fbx.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx_ = new Fbx;
	//pFbx_がnullptrじゃなかったらのチェックを入れたほうがいい
	pFbx_->Load("Player.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;
}

void Player::Update()
{
	transform_.rotate_.y += 1.0f;
	if (transform_.rotate_.y > 360.0f)
	{
		KillMe();
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