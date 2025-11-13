#include "SceneManager.h"
#include "..\\PlayScene.h"
#include "..\\TitleScene.h"
#include "Direct3D.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.front();
		scene->ReleaseSub();
		SAFE_DELETE(scene);
		childList_.clear();
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		case SCENE_ID_BUTTLE:
			break;
		case SCENE_ID_CLEAR:
			break;
		case SCENE_ID_GAMEOVER:
			break;
		case SCENE_ID_MAX:
			break;
		default:
			break;
		}
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID nextScene)
{
	nextSceneID_ = nextScene;
}
