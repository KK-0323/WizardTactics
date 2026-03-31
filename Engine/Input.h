#pragma once

#include <dInput.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyUp(int keyCode);
	bool IsKeyDown(int keyCode);

	// É}ÉEÉXÇÃèÛë‘
	XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
	bool IsMouseButton(int btnCode);
	bool IsMouseButtonUp(int btnCode);
	bool IsMouseButtonDown(int btnCode);
	void Release();
};