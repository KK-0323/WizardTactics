#include "Enemy.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx_(nullptr), initialX_(0.0f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Enemy.fbx");
	transform_.position_ = { 20.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;
	initialX_ = transform_.position_.x;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Enemy::Update()
{
	time_ += DELTA_TIME;

	float offsetX = amplitude_ * std::sin(speed_ * time_);

	transform_.position_.x = initialX_ + offsetX;
}

void Enemy::Draw()
{
	pFbx_->Draw(transform_);
}

void Enemy::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}

void Enemy::OnCollision(GameObject* pTarget)
{
	MessageBoxA(0, "“–‚½‚Á‚½", "Collider", MB_OK);
}