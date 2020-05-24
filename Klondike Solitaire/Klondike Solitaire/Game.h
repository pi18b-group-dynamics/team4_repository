#pragma once

#include <Windows.h>
#include <string>

#include "Video.h"
#include "Audio.h"
#include "Shell.h"
#include "Input.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	bool Init(HINSTANCE hInstance, PSTR pScmdline);
	void Destroy();
	void Run();
	std::wstring ErrMsg();
private:
	bool Initialize();
	std::wstring TextMsg;
};