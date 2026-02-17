#include "Stage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

Stage::Stage(GameObject* parent, std::string modelPath)
	:GameObject(parent, "Stage"), hModel_(-1), modelPath_(modelPath)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load(modelPath_);
	assert(hModel_ >= 0);
	transform_.scale_.z = 3.0f;

	float cX = 0.5f;
	float cY = 0.5f;
	float cZ = 0.5f;

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
	Model::Release();
}

void Stage::OnCollision(GameObject* pTarget)
{
}
