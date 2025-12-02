#include "Enemy.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"
#include "Engine\\SceneManager.h"

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
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 20.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;
	initialX_ = transform_.position_.x;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Enemy::Update()
{
	//time_ += DELTA_TIME;

	//float offsetX = amplitude_ * std::sin(speed_ * time_);

	//transform_.position_.x = initialX_ + offsetX;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetName() == "Player")
	{
		//MessageBoxA(0, "‚Ô‚Â‚©‚Á‚½", "Collider", MB_OK);
		GameObject* sceneObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_BUTTLE);
			}
		}
	}
	
}