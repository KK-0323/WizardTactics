#include "Ally.h"
#include "Player.h"

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr), moveSpeed__(0.5f), pTargetPlayer_(nullptr)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Ally.fbx");
	transform_.position_ = { -20.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	
}

void Ally::Update()
{
	// ポインタ取得
	pTargetPlayer_ = FindObject("Player");
	// Playerの位置に合わせて追従
	if (pTargetPlayer_)
	{
		const XMFLOAT3& playerPos = pTargetPlayer_->GetPosition();

		XMFLOAT3 targetPos = playerPos;
		targetPos.x = -1.0f;

		transform_.position_ = targetPos;
	}

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
