#pragma once

#include "BaseCollider.h"

// 超簡単球体コライダークラス
class SphereCollider : public BaseCollider
{
public:
	SphereCollider(float radius);
	float GetRadius() { return (radius_); } // インライン定義

	// コライダーのタイプ
	ColliderType GetType() const override { return SPHERE; }

private:
	float radius_; // 半径
};