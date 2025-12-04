#pragma once
//#include <d3d11.h>
//#include <DirectXMath.h>

//class SphereCollider;
//class BoxCollider;

class BaseCollider
{
public:
	enum ColliderType
	{
		SPHERE,
		BOX
	};

	virtual ~BaseCollider() = default;

	virtual ColliderType GetType() const = 0;

protected:
	BaseCollider() = default;
};

