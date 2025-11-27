#include "Stage.h"
#include <fstream>
#include <sstream>
#include <string>

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), pFbx_(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Stage.fbx");
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	transform_.scale_ = { 5.0f, 1.0f, 1.0f };
}

void Stage::Update()
{
	//transform_.rotate_.y += 0.5f;
}

void Stage::Draw()
{
	if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void Stage::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
