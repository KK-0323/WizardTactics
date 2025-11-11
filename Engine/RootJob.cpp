#include "RootJob.h"
#include "..\PlayScene.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	Instantiate<PlayScene>(this);
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
