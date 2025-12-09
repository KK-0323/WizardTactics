#include "ButtleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
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
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Stage>(this);
}

void ButtleScene::Update()
{
	//プレイヤーに視点が追従
	GameObject* pPlayer = FindObject("Player");
	if (pPlayer != nullptr)
	{
		XMFLOAT3 pPos = pPlayer->GetPosition();
		XMVECTOR playerPos = XMLoadFloat3(&pPos);

		XMVECTOR cameraOffset = XMVectorSet(0.0f, 15.0f, -20.0f, 0.0f);
		XMVECTOR cameraPos = XMVectorAdd(playerPos, cameraOffset);

		XMVECTOR targetOffset = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
		XMVECTOR targetPos = XMVectorAdd(playerPos, targetOffset);

		Camera::SetPosition(cameraPos);
		Camera::SetTarget(targetPos);

		Camera::Update();
	}
}

void ButtleScene::Draw()
{
}

void ButtleScene::Release()
{
}
