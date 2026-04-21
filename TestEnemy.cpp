#include "TestEnemy.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

TestEnemy::TestEnemy(GameObject* parent)
	:GameObject(parent, "TestEnemy"), pFbx_(nullptr)
{
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Initialize()
{
	hModel_ = Model::Load("TestEnemy.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 5.0f,3.0f,0.0f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void TestEnemy::Update()
{
}

void TestEnemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestEnemy::Release()
{
	Model::Release();
}

void TestEnemy::OnCollision(GameObject* pTarget)
{
}
