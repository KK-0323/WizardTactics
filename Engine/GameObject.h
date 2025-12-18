#pragma once

#include <list>
#include <string>
#include <algorithm>
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
	const XMFLOAT3& GetScale() const { return transform_.scale_; }

	// 生成したオブジェクトのポインタを返すようにした
	template <typename T>
	T* Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}

	template <typename T, typename Arg1>
	T* Instantiate(GameObject* parent, Arg1 arg1)
	{
		T* obj = new T(parent, arg1);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}

	string GetName() const { return objectName_; }

	virtual int GetLevel() const { return currentLevel_; }
	void SetLevel(int level) { currentLevel_ = level; }

protected:
	list<GameObject* > childList_;
	Transform transform_;
	GameObject* pParent_;
	string objectName_;
	BaseCollider* pCollider_;
	int currentLevel_; 

private:
	bool isDead_;
};