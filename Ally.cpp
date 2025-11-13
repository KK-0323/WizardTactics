#include "Ally.h"

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Ally.fbx");
	transform_.position_ = { 0.0f, 0.0f, 30.0f };
}

void Ally::Update()
{
}

void Ally::Draw()
{
	pFbx_->Draw(transform_);
}

void Ally::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
