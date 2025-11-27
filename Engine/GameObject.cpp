#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name)
{
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

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	float thisR = this->pCollider_->GetRadius();
	float tgtR = pTarget->pCollider_->GetRadius();
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
		//③なんかする
		//MessageBoxA(0, "ぶつかった", "Collider", MB_OK);
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
