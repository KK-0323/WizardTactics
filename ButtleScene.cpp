#include "ButtleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "ButtleStage.h"
#include "Ally.h"
#include "Engine\\Camera.h"

ButtleScene::ButtleScene(GameObject* parent)
	:GameObject(parent, "ButtleScene")
{
}

ButtleScene::~ButtleScene()
{
}

void ButtleScene::Initialize()
{
	Instantiate<Enemy>(this);
	Instantiate<ButtleStage>(this);

	Camera::Initialize();
	Camera::Update();

	GameObject* pPlayer = FindObject("Player");
	if (pPlayer != nullptr)
	{
		XMFLOAT3 playerPos = { -5.0f, 0.0f,0.0f };
		pPlayer->SetPosition(playerPos);
	}

	GameObject* pAlly = FindObject("Ally");
	if (pAlly != nullptr)
	{
		XMFLOAT3 allyPos = { 0.0f, 0.0f, 0.0f };
		pAlly->SetPosition(allyPos);
	}
}

void ButtleScene::Update()
{
}

void ButtleScene::Draw()
{
}

void ButtleScene::Release()
{
}
