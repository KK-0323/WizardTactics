#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Ally.h"
#include "Stage.h"
#include "Engine\\SceneManager.h"
#include "Engine\\Camera.h"
#include "Engine\\Input.h"
#include "Engine\\Model.h"
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
	Instantiate<StageManager>(this);
	auto player = Instantiate<Player>(this);
	auto zEnemy = Instantiate<Enemy>(this, ENEMY_ZAKO);
	auto bEnemy = Instantiate<Enemy>(this, ENEMY_BOSS);
	auto ally = Instantiate<Ally>(this);

	ally->SetTargetEnemy(zEnemy);
}

void PlayScene::Update()
{
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
	Model::AllRelease();
}
