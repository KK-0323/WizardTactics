#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Ally.h"
#include "BattleStage.h"
#include "Engine\\SceneManager.h"
#include "Engine\\Camera.h"
#include "Engine\\Input.h"
#include "Engine\\Model.h"
#include "StageManager.h"

BattleScene::BattleScene(GameObject* parent)
	:GameObject(parent, "BattleScene")
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Initialize()
{
	Instantiate<StageManager>(this);
	auto player = Instantiate<Player>(this);
	auto zEnemy = Instantiate<Enemy>(this, ENEMY_ZAKO);
	auto bEnemy = Instantiate<Enemy>(this, ENEMY_BOSS);
	auto ally = Instantiate<Ally>(this);

	ally->SetTargetEnemy(zEnemy);
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
	if (Input::IsKeyDown(DIK_C))
	{
		GameObject* sceneManagerObj = this->GetRootJob()->FindObject("SceneManager");
		if (sceneManagerObj != nullptr)
		{
			SceneManager* sceneManager = dynamic_cast<SceneManager*>(sceneManagerObj);
			if (sceneManager != nullptr)
			{
				sceneManager->ChangeScene(SCENE_ID_CLEAR);
			}
		}
	}
}

void BattleScene::Draw()
{
}

void BattleScene::Release()
{
	Model::AllRelease();
}
