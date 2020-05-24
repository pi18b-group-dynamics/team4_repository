#include "Game.h"

GameEngine::GameEngine()
{}

GameEngine::GameEngine(const GameEngine&)
{}

GameEngine::~GameEngine()
{}

bool GameEngine::Init(HINSTANCE hInstance, PSTR pScmdline)
{
	//Shell = new ShellCore();
	//Audio = new AudioCore();
	//Input = new InputCore();
	//Video = new VideoCore();
	/*if(!Shell->Init())
	{
		TextMsg += L"Ошибка инициализации ядра оболочки";
		return false;
	}
	if(!Initialize())
	{
		TextMsg += L"Ошибка инициализации объекта Engine";
		return false;
	}
	if(!Audio->Init())
	{
		TextMsg += L"Ошибка инициализации звукового устройства";
		return false;
	}
	if(!Input->Init())
	{
		TextMsg += L"Ошибка инициализации обработки ввода";
		return false;
	}
	if(!Video->Init())
	{
		TextMsg += L"Ошибка инициализации видеодрайвера";
		return false;
	}*/
	return true;
}

void GameEngine::Destroy()
{}

void GameEngine::Run()
{}

std::wstring GameEngine::ErrMsg()
{
	return TextMsg;
}

bool GameEngine::Initialize()
{
	return false;
}
