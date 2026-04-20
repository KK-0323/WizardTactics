#include "TestScene.h"
#include "TestStage.h"
#include "TestPlayer.h"
#include "TestAlly.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	Instantiate<TestStage>(this);
	Instantiate<TestPlayer>(this);
	Instantiate<TestAlly>(this);
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
