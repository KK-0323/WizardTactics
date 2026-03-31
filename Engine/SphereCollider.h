#pragma once

#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
	SphereCollider(float radius);
	float GetRadius() { return (radius_); }

	// コライダーのタイプ
	ColliderType GetType() const override { return SPHERE; }

private:
	float radius_;
};