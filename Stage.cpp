#include "Stage.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), pFbx_(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Stage.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, -1.0f, 0.0f };
	transform_.scale_.x += 10.0f;

	SphereCollider* col = new SphereCollider(0.5f);
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
