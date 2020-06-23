#include "Shell.h"
#include <string>

Audio* a;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}

int WINAPI WinMain(HINSTANCE hi, HINSTANCE prev, LPSTR cmdLine, int cmdShow)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hi;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "e";
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.


		// If windowed then set it to 800x600 resolution.
	screenWidth = 800;
	screenHeight = 600;

	// Place the window in the middle of the screen.
	posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;


	// Create the window with the screen settings and get the handle to it.
	HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW, "e", "e",
		WS_EX_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, hi, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);
	a = new Audio();
	a->Init(hwnd);
	a->LoadSound("Sounds\\Background\\background1.wav", true);
	a->LoadSound("Sounds\\Background\\background2.wav", true);
	a->LoadSound("Sounds\\Background\\Menu.wav", true);
	a->LoadSound("Sounds\\Effects\\FlippingOverCard.wav", false);
	a->LoadSound("Sounds\\Effects\\MovingCard.wav", false);
	a->LoadSound("Sounds\\Effects\\Victory.wav", false);
	a->SetVolume(10);
	//a->PlayBack(3);
	MSG msg;
	bool done, result;
	Input* i = new Input();
	i->Init(hi, hwnd, 800, 600);


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	std::string s = "";
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		i->Frame();
		RECT r;
		r.left = 5;
		r.right = 90;
		r.top = 5;
		r.bottom = 300;
		if (i->IsMousePressed())
		{

		}
		else
		{
		}
		if (i->IsEscapePressed())
		{
			done = true;
		}
		SetWindowText(hwnd, s.c_str());
	}
	return 0;
}
