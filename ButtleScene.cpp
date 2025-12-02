#include "ButtleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

ButtleScene::ButtleScene(GameObject* parent)
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
}

void ButtleScene::Draw()
{
}

void ButtleScene::Release()
{
}
