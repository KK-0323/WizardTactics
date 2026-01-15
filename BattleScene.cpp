#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleStage.h"
#include "Ally.h"
#include "Engine\\Camera.h"
#include "Engine\\SceneManager.h"
#include "Engine\\Input.h"

BattleScene::BattleScene(GameObject* parent)
	:GameObject(parent, "BattleScene")
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Initialize()
{
	Camera::Initialize();
	Camera::Update();

	GameObject* pPlayer = FindObject("Player");
	if (pPlayer != nullptr)
	{
		XMFLOAT3 playerPos = { 0.0f, 0.0f,0.0f };
		pPlayer->SetPosition(playerPos);
		Instantiate<Player>(this);
	}

	GameObject* pAlly = FindObject("Ally");
	if (pAlly != nullptr)
	{
		XMFLOAT3 allyPos = { -2.0f, 0.0f, 0.0f };
		pAlly->SetPosition(allyPos);
		Instantiate<Ally>(this);
	}

	Instantiate<Enemy>(this);
	Instantiate<BattleStage>(this);
}

void BattleScene::Update()
{
	if (Input::IsKeyDown(DIK_P))
	{
		GameObject* sceneManagerObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneManagerObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneManagerObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_PLAY);
			}
		}
	}
}

void BattleScene::Draw()
{
}

void BattleScene::Release()
{
}
