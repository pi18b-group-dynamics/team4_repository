#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GameEngine* Engine;
	Engine = new GameEngine();
	if(!Engine->Init(hInstance, pScmdline))
	{
		Engine->Destroy();
		MessageBox(NULL, Engine->ErrMsg().c_str(), L"Error", MB_OK);
		return 0;
	}
	Engine->Run();
	Engine->Destroy();
	return 0;
}