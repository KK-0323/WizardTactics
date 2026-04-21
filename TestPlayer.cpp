#include "TestPlayer.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent, "TestPlayer"), pFbx_(nullptr)
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Initialize()
{
	hModel_ = Model::Load("TestPlayer.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,3.0f,0.0f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void TestPlayer::Update()
{
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 1.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 1.0f;
	}
	if (Input::IsKeyDown(DIK_1))
	{
		currentCommand_ = CommandType::ATTACK;
	}
	if (Input::IsKeyDown(DIK_0))
	{
		currentCommand_ = CommandType::NONE;
	}
}

void TestPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestPlayer::Release()
{
	Model::Release();
}

void TestPlayer::OnCollision(GameObject* pTarget)
{
}
