#include "TestScene.h"
#include "TestStage.h"
#include "TestPlayer.h"
#include "TestAlly.h"
#include "TestEnemy.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	auto stage = Instantiate<TestStage>(this);
	auto player = Instantiate<TestPlayer>(this);
	auto enemy = Instantiate<TestEnemy>(this);
	auto ally = Instantiate<TestAlly>(this);

	ally->SetTargetEnemy(enemy);
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
