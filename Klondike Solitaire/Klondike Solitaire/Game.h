#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Pdh.h>
#include <string>

#include "Audio.h"
#include "Input.h"
#include "Shell.h"
#include "Video.h"

#pragma comment(lib, "pdh.lib")

class GameEngine
{
public:
	GameEngine();
	GameEngine(const GameEngine&);
	~GameEngine();
	bool Init(HINSTANCE hInstance, PSTR pScmdline);
	void Destroy();
	void Run();
	bool Frame();
	void Perfomance();
	std::wstring ErrMsg();
	bool Initialize();
private:
	std::wstring TextMsg;//Сообщение об ошибке
	VideoCore* Video;//Графический модуль
	InputCore* Input;//Устройство ввода
	AudioCore* Audio;//Звуковое устройство
	ShellCore* Shell;//Скриптооболочка
	INT64 frencuency;//Скорость процессора в командах/сек
	INT64 starttime;//Время последнего фрейма
	INT64 frametime;//Длительность обработки фрейма
	int FPS;//Кол-во кадров в сек
	bool canReadCpu;//Поддерживает ли процессор чтение производительности
	HQUERY queryHandle;//Указатель на запрос производительности
	HCOUNTER counterHandle;//Указатель на счетчик производительности
	unsigned long lastSampleTime;//Время последнего запроса производительности
	INT64 CPU;//Нагрузка на процессор в процентах
	HWND window;//Дескриптор окна
};
#endif