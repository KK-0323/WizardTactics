#pragma once

#include "BaseCollider.h"
#include <DirectXMath.h>

class BoxCollider : public BaseCollider
{
public:
	BoxCollider(const DirectX::XMFLOAT3& halfExtent);

	// コライダーのタイプ
	ColliderType GetType() const override { return BOX; }

	// サイズを取得する関数
	const DirectX::XMFLOAT3& GetHalfExtent() const { return halfExtent_; }

private:
	// 中心から各軸方向への半分の長さ
	DirectX::XMFLOAT3 halfExtent_;
};