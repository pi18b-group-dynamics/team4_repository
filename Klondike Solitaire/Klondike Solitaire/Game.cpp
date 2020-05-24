#include "Game.h"

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{}

bool GameEngine::Init(HINSTANCE hInstance, PSTR pScmdline)
{
	if(!Initialize())
	{
		TextMsg += L"Ошибка инициализации объекта Engine";
		return false;
	}
	
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
