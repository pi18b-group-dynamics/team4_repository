#pragma once

#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
public:
	Input();
	~Input();
	bool Init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
	void Destroy();
	bool Frame();

	bool IsEscapePressed();
	bool IsMousePressed();
	void GetMouseLocation(int& mouseX, int& mouseY);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};