#include "Input.h"

namespace Input
{
	//キーボードインプット
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256] = { 0 };
	//マウスインプット
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE mouseState; // マウスの状態
	DIMOUSESTATE prevMouseState; // 前回のマウスの状態
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		// キーボードの初期化
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		// マウスの初期化
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		// キーボードの状態を保存
		memcpy(prevKeyState, keyState, sizeof(keyState)); // ブロックコピー
		for (auto i = 0; i < 256; i++)
		{
			prevKeyState[i] = keyState[i];
		}

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		// マウスの状態を保存
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));
		pMouseDevice->Acquire();
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 128)
			if (keyState[keyCode] & 0x80)
			{
				return true;
			}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は離していて、前回は押している
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		//mousePosition = XMVectorSet((float)x, (float)y, 0.0f, 0.0f);
		mousePosition = { (float)x, (float)y, 0.0f, 0.0f };
	}

	bool IsMouseButton(int btnCode)
	{
		if (mouseState.rgbButtons[btnCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int btnCode)
	{
		if (!IsMouseButton(btnCode) && (prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int btnCode)
	{
		if (IsMouseButton(btnCode) && !(prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}