#include "ButtleStage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

ButtleStage::ButtleStage(GameObject* parent)
	:GameObject(parent, "ButtleStage"), pFbx_(nullptr)
{
}

ButtleStage::~ButtleStage()
{
}

void ButtleStage::Initialize()
{
	hModel_ = Model::Load("ButtleStage.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,0.0f,0.0f };
}

void ButtleStage::Update()
{
}

void ButtleStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void ButtleStage::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void ButtleStage::OnCollision(GameObject* pTarget)
{
}
