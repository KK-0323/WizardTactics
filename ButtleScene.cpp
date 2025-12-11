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
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Ally>(this);
	Instantiate<ButtleStage>(this);

	Camera::Initialize();
	Camera::Update();
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
