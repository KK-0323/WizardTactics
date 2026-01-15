#include "BattleStage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

BattleStage::BattleStage(GameObject* parent)
	:GameObject(parent, "BattleStage"), pFbx_(nullptr)
{
}

BattleStage::~BattleStage()
{
}

void BattleStage::Initialize()
{
	hModel_ = Model::Load("BattleStage.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,0.0f,0.0f };
	transform_.rotate_.y = 90.0f;

	BoxCollider* col = new BoxCollider({ 14.0f, 1.0f, 14.0f });
	AddCollider(col);
}

void BattleStage::Update()
{
}

void BattleStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void BattleStage::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void BattleStage::OnCollision(GameObject* pTarget)
{
}
