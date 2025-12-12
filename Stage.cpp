#include "Stage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), pFbx_(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Road.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,-1.0f, 0.0f };
	transform_.scale_ = { 50.0f, 1.0f, 4.0f };

	float cX = transform_.scale_.x * 0.5f;
	float cY = transform_.scale_.y * 1.0f;
	float cZ = transform_.scale_.z * 1.0f;

	BoxCollider* col = new BoxCollider({ cX, cY, cZ });
	AddCollider(col);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void Stage::OnCollision(GameObject* pTarget)
{
}
