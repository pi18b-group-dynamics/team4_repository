#include "Game.h"

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{}

bool GameEngine::Init(HINSTANCE hInstance, PSTR pScmdline)
{
	return false;
}

void GameEngine::Destroy()
{}

void GameEngine::Run()
{}

std::wstring GameEngine::ErrMsg()
{
	return std::wstring();
}
