#include "GameObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include <Windows.h>

namespace Compatibility
{
	const float EFFECTIVE = 1.5f;
	const float NORMAL = 1.0f;
	const float RESIST = 0.5f;
}

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), currentLevel_(1)
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
	std::list<GameObject*> safeChildList = this->childList_;
	for (auto child : safeChildList)
	{
		if (!child->isDead_)
		{
			child->UpdateSub();
		}
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
		pCollision = SPHEREBOX;
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
	{
		BoxCollider* thisB = static_cast<BoxCollider*>(pCollider_);
		BoxCollider* tgtB = static_cast<BoxCollider*>(pTarget->pCollider_);

		// 自分の判定情報
		const DirectX::XMFLOAT3& thisHalf = thisB->GetHalfExtent();
		const DirectX::XMFLOAT3& thisPos = transform_.position_;

		// 相手の判定情報
		const DirectX::XMFLOAT3& tgtHalf = tgtB->GetHalfExtent();
		const DirectX::XMFLOAT3& tgtPos = pTarget->GetPosition();

		// 中心距離の計算
		float distX = abs(thisPos.x - tgtPos.x);
		float distY = abs(thisPos.y - tgtPos.y);
		float distZ = abs(thisPos.z - tgtPos.z);

		// 衝突の閾値計算
		float threX = thisHalf.x + tgtHalf.x;
		float threY = thisHalf.y + tgtHalf.y;
		float threZ = thisHalf.z + tgtHalf.z;

		// 判定
		if (distX <= threX &&
			distY <= threY &&
			distZ <= threZ)
		{
			OnCollision(pTarget);
		}
	}
	break;
	case SPHEREBOX:
	{
		// 球と四角形の情報
		SphereCollider* pSphere;
		BoxCollider* pBox;
		const DirectX::XMFLOAT3* pSpherePos;
		const DirectX::XMFLOAT3* pBoxPos;

		if (thisType == BaseCollider::SPHERE)
		{
			pSphere = static_cast<SphereCollider*>(pCollider_);
			pBox = static_cast<BoxCollider*>(pTarget->pCollider_);
			pSpherePos = &transform_.position_;
			pBoxPos = &pTarget->GetPosition();
		}
		else // 相手が球の場合
		{
			pSphere = static_cast<SphereCollider*>(pTarget->pCollider_);
			pBox = static_cast<BoxCollider*>(pCollider_);
			pSpherePos = &pTarget->GetPosition();
			pBoxPos = &transform_.position_;
		}

		const DirectX::XMFLOAT3& halfExtent = pBox->GetHalfExtent();
		const DirectX::XMFLOAT3& boxScale = pBox == pCollider_ ? transform_.scale_ : pTarget->GetScale();

		XMFLOAT3 worldHalfExtent;
		worldHalfExtent.x = halfExtent.x * boxScale.x;
		worldHalfExtent.y = halfExtent.y * boxScale.y;
		worldHalfExtent.z = halfExtent.z * boxScale.z;

		XMFLOAT3 closestPoint;
		XMFLOAT3 sphereCenter = *pSpherePos;
		XMFLOAT3 boxCenter = *pBoxPos;

		closestPoint.x = max(boxCenter.x - worldHalfExtent.x, min(sphereCenter.x, boxCenter.x + worldHalfExtent.x));
		closestPoint.y = max(boxCenter.y - worldHalfExtent.y, min(sphereCenter.y, boxCenter.y + worldHalfExtent.y));
		closestPoint.z = max(boxCenter.z - worldHalfExtent.z, min(sphereCenter.z, boxCenter.z + worldHalfExtent.z));

		float dx = sphereCenter.x - closestPoint.x;
		float dy = sphereCenter.y - closestPoint.y;
		float dz = sphereCenter.z - closestPoint.z;

		float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);

		float radius = pSphere->GetRadius();
		float radiusSquared = radius * radius;

		if (distanceSquared <= radiusSquared)
		{
			OnCollision(pTarget);
		}
	}
	break;
	case PAIR_MAX:
	break;
	default:
		break;
	}	
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//①自分にコライダーがなかったらreturn
		if (pCollider_ == nullptr || pTarget == nullptr)
			return;
	//②自分とターゲット自体のコライダーの当たり判定
	if (pTarget->pCollider_ != nullptr && pTarget->pCollider_ != pCollider_)
		Collision(pTarget);
	//③再帰的なやつで、ターゲットの子オブジェクトを当たり判定してく
	std::list<GameObject*> safeChildList = pTarget->childList_;
	for (auto itr : safeChildList)
	{
		if (itr != nullptr && !itr->isDead_)
		{
			RoundRobin(itr);
		}
	}
		
}

void GameObject::OnCollision(GameObject* pTarget)
{
	float damageMultiplier = 1.0f;

	switch (this->attackType_)
	{
	case AttackType::NONE:
		break;
	case AttackType::SLASH:
		if (pTarget->defenseType_ == DefenseType::SOFT)
		{
			damageMultiplier = 1.5f;
		}
		if (pTarget->defenseType_ == DefenseType::HARD)
		{
			damageMultiplier = 0.5f;
		}
		break;
	case AttackType::BLUNT:
		if (pTarget->defenseType_ == DefenseType::HARD)
		{
			damageMultiplier = 1.5f;
		}
		if (pTarget->defenseType_ == DefenseType::SPIRIT)
		{
			damageMultiplier = 0.5f;
		}
		break;
	case AttackType::MAGIC:
		if (pTarget->defenseType_ == DefenseType::SPIRIT)
		{
			damageMultiplier = 1.5f;
		}
		if (pTarget->defenseType_ == DefenseType::SOFT)
		{
			damageMultiplier = 0.8f;
		}
		break;
	}
}

float GameObject::GetPhysicalCalculation(AttackType atk, DefenseType def)
{
	if (atk == AttackType::SLASH)
	{
		if (def == DefenseType::SOFT)
		{
			return Compatibility::EFFECTIVE;
		}
		else if (def == DefenseType::HARD)
		{
			return Compatibility::RESIST;
		}
		else
		{
			return Compatibility::NORMAL;
		}
	}
	if (atk == AttackType::BLUNT)
	{
		if (def == DefenseType::HARD)
		{
			return Compatibility::EFFECTIVE;
		}
		else if(def == DefenseType::SPIRIT)
		{
			return Compatibility::RESIST;
		}
		else
		{
			return Compatibility::NORMAL;
		}
	}
}

float GameObject::GetElementalCalculation(ElementType atk, ElementType def)
{
	if (atk == ElementType::FIRE && def == ElementType::THUNDER)
	{
		return Compatibility::EFFECTIVE;
	}
	if (atk == ElementType::THUNDER && def == ElementType::WATER)
	{
		return Compatibility::EFFECTIVE;
	}
	if (atk == ElementType::WATER && def == ElementType::FIRE)
	{
		return Compatibility::EFFECTIVE;
	}

	if (atk == ElementType::FIRE && def == ElementType::WATER)
	{
		return Compatibility::RESIST;
	}
	if (atk == ElementType::THUNDER && def == ElementType::FIRE)
	{
		return Compatibility::RESIST;
	}
	if (atk == ElementType::WATER && def == ElementType::THUNDER)
	{
		return Compatibility::RESIST;
	}

	return Compatibility::NORMAL;
}

int GameObject::CalculateDamage(int baseAtk, GameObject* pTarget)
{
	// 物理相性の取得
	float physCal = GetPhysicalCalculation(this->GetAttack(), pTarget->GetDefense());

	// 属性相性の取得
	float elemCal = GetElementalCalculation(this->GetElement(), pTarget->GetElement());

	// 総合計算
	float totalCal = (float)baseAtk * physCal * elemCal;
	return (int)totalCal;
}

void GameObject::ApplyDamage(int damage)
{
	if (isDead_)
	{
		return;
	}

	currentHp_ -= damage;
	
	if (currentHp_ <= 0)
	{
		currentHp_ = 0;
		isDead_ = true;
		KillMe();
	}
}


