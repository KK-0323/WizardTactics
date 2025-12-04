#include "GameObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include <Windows.h>

// 当たり判定のペア
enum PairCollsion
{
	SPHERES,
	BOXES,
	SPEREBOX
};

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = (&parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	//自分を描画
	this->Draw();
	for (auto child : this->childList_)
	{
		child->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	transform_.Calculation();
	this->Update();
	RoundRobin(GetRootJob());
	for (auto child : this->childList_)
	{
		child->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void GameObject::ReleaseSub()
{
	this->Release();
	for (auto child : this->childList_)
	{
		child->ReleaseSub();
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = { x,y,z };
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this; // RootJob
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const string& name)
{
	if (this->objectName_ == name)
	{
		return this;
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;
			}
		}
	}
	return this;
}

GameObject* GameObject::FindObject(const string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}

void GameObject::AddCollider(BaseCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	// 当たり判定のスキップ処理
	if (pCollider_ == nullptr || pTarget->pCollider_ == nullptr)
	{
		return;
	}

	// コライダーのタイプ取得
	BaseCollider::ColliderType thisType = pCollider_->GetType();
	BaseCollider::ColliderType targetType = pTarget->pCollider_->GetType();

	// ペアのタイプ
	PairCollsion pCollision;

	if (thisType == BaseCollider::SPHERE && targetType == BaseCollider::SPHERE)
	{
		pCollision = SPHERES;
	}
	else if (thisType == BaseCollider::BOX && targetType == BaseCollider::BOX)
	{
		pCollision = BOXES;
	}
	else if ((thisType == BaseCollider::SPHERE && targetType == BaseCollider::BOX) ||
		thisType == BaseCollider::BOX && targetType == BaseCollider::SPHERE)
	{
		pCollision = SPHERES;
	}

	// switch_caseでそれぞれのペアの処理振り分け
	switch (pCollision)
	{
	case SPHERES:
	{
		SphereCollider* thisS = static_cast<SphereCollider*>(pCollider_);
		SphereCollider* tgtS = static_cast<SphereCollider*>(pTarget->pCollider_);

		float thisR = thisS->GetRadius();
		float tgtR = tgtS->GetRadius();
		float thre = (thisR + tgtR) * (thisR + tgtR);
		//①２つのコライダーの距離計算をする
		XMFLOAT3 thisP = this->transform_.position_;
		XMFLOAT3 tgtP = pTarget->transform_.position_;
		float dist = (thisP.x - tgtP.x) * (thisP.x - tgtP.x) +
			(thisP.y - tgtP.y) * (thisP.y - tgtP.y) +
			(thisP.z - tgtP.z) * (thisP.z - tgtP.z);
		//②コライダー同士が交差していたら
		if (dist <= thre)
		{
			OnCollision(pTarget);
		}
	}
	break;
	case BOXES:
		break;
	case SPEREBOX:
		break;
	default:
		break;
	}	
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//①自分にコライダーがなかったらreturn
		if (pCollider_ == nullptr)
			return;
	//②自分とターゲット自体のコライダーの当たり判定
	if (pTarget->pCollider_ != nullptr && pTarget->pCollider_ != pCollider_)
		Collision(pTarget);
	//③再帰的なやつで、ターゲットの子オブジェクトを当たり判定してく
	for (auto itr : pTarget->childList_)
		RoundRobin(itr);
}

void GameObject::OnCollision(GameObject* pTarget)
{
}
