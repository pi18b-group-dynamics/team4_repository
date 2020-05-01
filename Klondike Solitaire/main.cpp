#include "Game.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS windowClass = {0};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = L"HELLO_WORLD";
    RegisterClass(&windowClass);

    HWND hwnd = CreateWindow(
        windowClass.lpszClassName,
        L"WinAPI Empty Window - Hello World",
        WS_OVERLAPPEDWINDOW,
        100, 50, 1280, 720,
        nullptr, nullptr,
        hInstance,
        nullptr);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}