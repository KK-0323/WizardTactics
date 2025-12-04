#pragma once

#include <list>
#include <string>
#include "Transform.h"
#include "BaseCollider.h"

class SphereCollider;
class BoxCollider;

using std::string;
using std::list;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	void KillMe();

	GameObject* GetRootJob();
	GameObject* FindChildObject(const string& name);
	GameObject* FindObject(const string& name);

	void AddCollider(BaseCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
	virtual void OnCollision(GameObject* pTarget);

	const XMFLOAT3& GetPosition() const { return transform_.position_; }

	template <typename T>
	void Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
	}

	string GetName() const { return objectName_; }

protected:
	list<GameObject* > childList_;
	Transform transform_;
	GameObject* pParent_;
	string objectName_;
	BaseCollider* pCollider_;

private:
	bool isDead_;
};