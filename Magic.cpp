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
	magicSpeed_(5.0f), magicID_(MAGIC_FIRE), spawnTimer_(0.0f)
{
}

Magic::~Magic()
{
}

void Magic::Initialize()
{
	SetAttackType(AttackType::MAGIC);

	switch (magicID_)
	{
	case MAGIC_FIRE:
		SetElementType(ElementType::FIRE);
		hModel_ = Model::Load("Fire.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_WATER:
		SetElementType(ElementType::WATER);
		hModel_ = Model::Load("Water.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_THUNDER:
		SetElementType(ElementType::THUNDER);
		hModel_ = Model::Load("Thunder.fbx");
		assert(hModel_ >= 0);
		break;
	case MAGIC_MAX:
		break;
	default:
		break;
	}

	transform_.position_.x = 3.0f;
	transform_.scale_ = { 0.5f,0.5f,0.5f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Magic::Update()
{
	transform_.position_.x += magicSpeed_ * DELTA_TIME;
	
	spawnTimer_ += DELTA_TIME;
	if (spawnTimer_ >= SPAWN_TIME)
	{
		//this->KillMe();
	}
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
	if (pTarget->GetName() == "Enemy")
	{
		//this->KillMe();
		int baseAtk = 20;
		int damage = this->CalculateDamage(baseAtk, pTarget);
		pTarget->ApplyDamage(damage);
	}
}
