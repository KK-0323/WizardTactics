#include "BattleStage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

BattleStage::BattleStage(GameObject* parent, std::string modelPath)
	:GameObject(parent, "BattleStage"), hModel_(-1), modelPath_(modelPath)
{
}

BattleStage::~BattleStage()
{
}

void BattleStage::Initialize()
{
	hModel_ = Model::Load(modelPath_);
	assert(hModel_ >= 0);
	transform_.scale_ = { 2.0f, 2.0f, 2.0f };

	float cX = 0.5f;
	float cY = 0.5f;
	float cZ = 0.5f;

	BoxCollider* col = new BoxCollider({ cX, cY, cZ });
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
	//Model::Release();
}

void BattleStage::OnCollision(GameObject* pTarget)
{
}
