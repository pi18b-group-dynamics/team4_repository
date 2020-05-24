#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>

#include "Audio.h"
#include "Input.h"
#include "Shell.h"
#include "Video.h"

class GameEngine
{
public:
	GameEngine();
	GameEngine(const GameEngine&);
	~GameEngine();
	bool Init(HINSTANCE hInstance, PSTR pScmdline);
	void Destroy();
	void Run();
	std::wstring ErrMsg();

	bool Initialize();
private:
	std::wstring TextMsg;
	VideoCore* Video;
};
#endif