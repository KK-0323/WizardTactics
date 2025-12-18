#include "TestStage.h"
#include "Engine\\Model.h"
#include "Engine\\BoxCollider.h"

TestStage::TestStage(GameObject* parent)
	:GameObject(parent, "ButtleStage"), pFbx_(nullptr)
{
}

TestStage::~TestStage()
{
}

void TestStage::Initialize()
{
	hModel_ = Model::Load("TestStage.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 180.0f;

	BoxCollider* col = new BoxCollider({ 25.0f, 1.0f, 1.0f });
	AddCollider(col);
}

void TestStage::Update()
{
}

void TestStage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestStage::Release()
{
	Model::Release();
}

void TestStage::OnCollision(GameObject* pTarget)
{
}
