#include "TestAlly.h"
#include "TestPlayer.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

TestAlly::TestAlly(GameObject* parent)
	:GameObject(parent, "TestAlly"), pFbx_(nullptr)
{
}

TestAlly::~TestAlly()
{
}

void TestAlly::Initialize()
{
	hModel_ = Model::Load("TestAlly.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -2.0f, 3.0f, 0.0f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
	
}

void TestAlly::Update()
{
	TestPlayer* pPlayer = (TestPlayer*)FindObject("TestPlayer");
	if (!pPlayer)return;

	CommandType command = pPlayer->GetCurrentCommand();

	if (command == CommandType::ATTACK)
	{
		transform_.position_.x = 8.0f;
	}
	else
	{
		transform_.position_.x = pPlayer->GetPosition().x - 2.0f;
	}
}

void TestAlly::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestAlly::Release()
{
	Model::Release();
}

void TestAlly::OnCollision(GameObject* pTarget)
{
}
