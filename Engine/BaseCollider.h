#pragma once

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

