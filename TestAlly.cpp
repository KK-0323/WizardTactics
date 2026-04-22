#include "TestAlly.h"
#include "Engine\\Model.h"
#include "Engine\\Input.h"
#include "Engine\\SphereCollider.h"

TestAlly::TestAlly(GameObject* parent)
	:GameObject(parent, "TestAlly"), pFbx_(nullptr),
	pPlayer_(nullptr), pEnemy_(nullptr)
{
}

TestAlly::~TestAlly()
{
}

void TestAlly::Initialize()
{
	hModel_ = Model::Load("TestAlly.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { -2.0f, 3.0f, 0.0f };

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
	
}

void TestAlly::Update()
{
	if (pEnemy_ == nullptr)
	{
		pEnemy_ = FindObject("TestEnemy");
	}
	if (pEnemy_)
	{
		char buf[256];
		sprintf_s(buf, "Found Object Name: %s, Address: %p\n", pEnemy_->GetName().c_str(), pEnemy_);
		OutputDebugStringA(buf);
		//XMFLOAT3 enemyPos = pEnemy_->GetPosition();
	}
	//CommandPattern();
	if (Input::IsKeyDown(DIK_1))
	{
		currentCommand_ = CommandType::ATTACK;
	}
	if (Input::IsKeyDown(DIK_0))
	{
		currentCommand_ = CommandType::NONE;
	}
}

void TestAlly::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestAlly::Release()
{
	Model::Release();
}

void TestAlly::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetName() == "TestEnemy")
	{
		int damage = CalculateDamage(10, pTarget);
		pTarget->ApplyDamage(damage);
	}
}

//void TestAlly::CommandPattern()
//{
//	if (currentCommand_ == CommandType::ATTACK)
//	{
//		pEnemy_ = FindObject("TestEnemy");
//		if (pEnemy_)
//		{
//			XMFLOAT3 enemyPos = pEnemy_->GetPosition();
//			XMFLOAT3 myPos = transform_.position_;
//
//			// 敵への方向ベクトル計算
//			float speed = 0.1f;
//			if (transform_.position_.x < enemyPos.x)
//			{
//				transform_.position_.x += speed;
//			}
//			//else if (transform_.position_.x > enemyPos.x)
//			//{
//			//	transform_.position_.x -= speed;
//			//}
//		}
//	}
//	else if (currentCommand_ == CommandType::NONE)
//	{
//		transform_.position_.x = -2.0f;
//	}
//}
