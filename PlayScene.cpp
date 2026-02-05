#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Ally.h"
#include "Stage.h"
#include "Engine\\SceneManager.h"
#include "Engine\\Camera.h"
#include "Engine\\Input.h"
#include "StageManager.h"

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
	Instantiate<Enemy>(this, ENEMY_ZAKO);
	Instantiate<Enemy>(this, ENEMY_BOSS);
	Instantiate<Ally>(this);
	Instantiate<StageManager>(this);
}

void PlayScene::Update()
{
	//プレイヤーに視点が追従
	GameObject* pPlayer = FindObject("Player");
	if (pPlayer != nullptr)
	{
		XMFLOAT3 pPos = pPlayer->GetPosition();
		XMVECTOR playerPos = XMLoadFloat3(&pPos);

		XMVECTOR cameraOffset = XMVectorSet(0.0f, 15.0f, -40.0f, 0.0f);
		XMVECTOR cameraPos = XMVectorAdd(playerPos, cameraOffset);

		XMVECTOR targetOffset = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
		XMVECTOR targetPos = XMVectorAdd(playerPos, targetOffset);

		Camera::SetPosition(cameraPos);
		Camera::SetTarget(targetPos);

		Camera::Update();
	}
	if (Input::IsKeyDown(DIK_B))
	{
		GameObject* sceneManagerObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneManagerObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneManagerObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_BATTLE);
			}
		}
	}
	
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
