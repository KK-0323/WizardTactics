#include "TestAlly.h"
#include "TestPlayer.h"
#include "Engine\\Model.h"
#include "Engine\\SphereCollider.h"

TestAlly::TestAlly(GameObject* parent)
	:GameObject(parent, "TestAlly"), pFbx_(nullptr)
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
	TestPlayer* pPlayer = (TestPlayer*)FindObject("TestPlayer");
	if (!pPlayer) return;

	CommandType command = pPlayer->GetCurrentCommand();

	if (command == CommandType::ATTACK)
	{
		GameObject* pEnemy = FindObject("TestEnemy");
		if (pEnemy)
		{
			XMFLOAT3 enemyPos = pEnemy->GetPosition();
			XMFLOAT3 myPos = transform_.position_;

			// 敵への方向ベクトル計算
			float speed = 0.1f;
			if (myPos.x < enemyPos.x)
			{
				myPos.x += speed;
			}
			else if (myPos.x > enemyPos.x)
			{
				myPos.x -= speed;
			}

			transform_.position_ = myPos;
		}
	}
	else
	{
		float followSpeed = 0.05f;
		XMFLOAT3 targetPos = pPlayer->GetPosition();
		targetPos.x -= 2.0f;

		if (transform_.position_.x < targetPos.x)
		{
			transform_.position_.x += followSpeed;
		}
		if (transform_.position_.x > targetPos.x)
		{
			transform_.position_.x -= followSpeed;
		}
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
