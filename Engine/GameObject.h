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

// 当たり判定のペア
enum PairCollsion
{
	SPHERES,
	BOXES,
	SPHEREBOX,
	PAIR_MAX
};

enum class AttackType
{
	NONE,	// 無
	SLASH,	// 斬撃
	BLUNT,	// 打撃
	MAGIC	// 魔法
};

enum class DefenseType
{
	NONE,	// 普通
	SOFT,	// 柔らかい
	HARD,	// 硬い
	SPIRIT	// 霊体
};

enum class ElementType
{
	NONE,
	FIRE,
	WATER,
	THUNDER
};

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

	void SetLevel(int level) { currentLevel_ = level; }
	void SetAttackType(AttackType type) { attackType_ = type; }
	void SetDefenseType(DefenseType type) { defenseType_ = type; }
	void SetElementType(ElementType type) { elementType_ = type; }

	string GetName() const { return objectName_; }
	virtual int GetLevel() const { return currentLevel_; }
	AttackType GetAttack() const { return attackType_; }
	DefenseType GetDefense() const { return defenseType_; }
	ElementType GetElement() const { return elementType_; }

	float GetPhysicalCalculation(AttackType atk, DefenseType def);
	float GetElementalCalculation(ElementType atk, ElementType def);
	int CalculateDamage(int baseAtk, GameObject* pTarget);

	void ApplyDamage(int damage);
	bool IsDead() const { return isDead_; }
protected:
	list<GameObject* > childList_;
	Transform transform_;
	GameObject* pParent_;
	string objectName_;
	BaseCollider* pCollider_;
	int currentLevel_; 
	int maxHp_;
	int currentHp_;
	bool isDead_ = false;
	DefenseType defenseType_ = DefenseType::NONE;
	AttackType attackType_ = AttackType::NONE;
	ElementType elementType_ = ElementType::NONE;

private:
	
};