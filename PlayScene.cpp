#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Ally.h"
#include "Engine\\Camera.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Ally>(this);
}

void PlayScene::Update()
{
	GameObject* pPlayer = FindObject("Player");
	if (pPlayer != nullptr)
	{
		XMFLOAT3 pPos = pPlayer->GetPosition();
		XMVECTOR playerPos = XMLoadFloat3(&pPos);

		XMVECTOR cameraOffset = XMVectorSet(0.0f, 0.0f, -40.0f, 0.0f);
		XMVECTOR cameraPos = XMVectorAdd(playerPos, cameraOffset);

		XMVECTOR targetOffset = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMVECTOR targetPos = XMVectorAdd(playerPos, targetOffset);

		Camera::SetPosition(cameraPos);
		Camera::SetTarget(targetPos);

		Camera::Update();
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
