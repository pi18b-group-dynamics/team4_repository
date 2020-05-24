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
	bool Init();
	void Destroy();
	void Run();
	std::wstring ErrMsg();
private:

};