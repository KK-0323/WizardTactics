#include "TitleScene.h"
#include "Engine\\Input.h"
#include "Engine\\SceneManager.h"
#include "Stage.h"
#include "TestStage.h"
#include "Engine\\Camera.h"
#include "Player.h"
#include "Ally.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//Instantiate<Player>(this);
	//Instantiate<Ally>(this);
}

void TitleScene::Update()
{
	//プレイヤーに視点が追従
	//GameObject* pPlayer = FindObject("Player");
	//if (pPlayer != nullptr)
	//{
	//	XMFLOAT3 pPos = pPlayer->GetPosition();
	//	XMVECTOR playerPos = XMLoadFloat3(&pPos);

	//	XMVECTOR cameraOffset = XMVectorSet(0.0f, 15.0f, -40.0f, 0.0f);
	//	XMVECTOR cameraPos = XMVectorAdd(playerPos, cameraOffset);

	//	XMVECTOR targetOffset = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	//	XMVECTOR targetPos = XMVectorAdd(playerPos, targetOffset);

	//	Camera::SetPosition(cameraPos);
	//	Camera::SetTarget(targetPos);

	//	Camera::Update();
	//}
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

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
