#include "Magic.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

const float DELTA_TIME = 1.0f / 60.0f;

Magic::Magic(GameObject* parent)
	:GameObject(parent, "Magic"), pFbx_(nullptr),
	magicSpeed_(5.0f)
{
}

Magic::Magic(GameObject* parent, MAGIC_ID id)
	:GameObject(parent, "Magic"), pFbx_(nullptr),
	magicSpeed_(5.0f), magicID_(MAGIC_FIRE)
{
}

Magic::~Magic()
{
}

void Magic::Initialize()
{
	switch (magicID_)
	{
	case MAGIC_FIRE:
		hModel_ = Model::Load("Fire.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_WATER:
		hModel_ = Model::Load("Water.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_THUNDER:
		hModel_ = Model::Load("Thunder.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_MAX:
		break;
	default:
		break;
	}

	transform_.scale_ = { 0.5f,0.5f,0.5f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Magic::Update()
{
	transform_.position_.x += magicSpeed_ * DELTA_TIME;
}

void Magic::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Magic::Release()
{
	Model::Release();
}

void Magic::OnCollision(GameObject* pTarget)
{
}
