#include "Ally.h"
#include "Player.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

Ally::Ally(GameObject* parent)
	:GameObject(parent, "Ally"), pFbx_(nullptr), moveSpeed__(0.5f), pTargetPlayer_(nullptr)
{
}

Ally::~Ally()
{
}

void Ally::Initialize()
{
	hModel_ = Model::Load("Ally.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -1.0f, 0.0f, 0.0f };
	transform_.rotate_.y = 90.0f;

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Ally::Update()
{
	//// ポインタ取得
	//pTargetPlayer_ = FindObject("Player");
	//// Playerの位置に合わせて追従
	//if (pTargetPlayer_)
	//{
	//	const XMFLOAT3& playerPos = pTargetPlayer_->GetPosition();

	//	XMFLOAT3 targetPos = playerPos;
	//	targetPos.x = -1.0f;

	//	transform_.position_ = targetPos;
	//}

}

void Ally::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ally::Release()
{
	if (pFbx_)
	{
		Model::Release();
	}
}

void Ally::OnCollision(GameObject* pTarget)
{
}
