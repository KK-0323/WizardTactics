#include "TestPlayer.h"
#include "Engine\\Input.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent, "TestPlayer")
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Initialize()
{
}

void TestPlayer::Update()
{
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
}

void TestPlayer::Release()
{
}

void TestPlayer::OnCollision(GameObject* pTarget)
{
}
