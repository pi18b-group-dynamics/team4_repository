#include "Game.h"

GameEngine::GameEngine()
{
	Video = nullptr;
	Input = nullptr;
	Audio = nullptr;
	Shell = nullptr;
}

GameEngine::GameEngine(const GameEngine&)
{}

GameEngine::~GameEngine()
{}

bool GameEngine::Init(HINSTANCE hInstance, PSTR pScmdline)
{
	Shell = new ShellCore();
	Audio = new AudioCore();
	Input = new InputCore();
	Video = new VideoCore();
	if(!Shell->Init())
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
	if(!Video->Init(640, 480, &window))
	{
		TextMsg += L"Ошибка инициализации видеодрайвера";
		return false;
	}
	return true;
}

void GameEngine::Destroy()
{
	if(canReadCpu)
		PdhCloseQuery(queryHandle);
}

void GameEngine::Run()
{
	MSG msg;
	bool done;
	ZeroMemory(&msg, sizeof(MSG));
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(msg.message == WM_QUIT)
			break;
		else
		{
			if(!Frame())
				break;
		}
	}
}

bool GameEngine::Frame()
{
	Perfomance();
	return true;
}

void GameEngine::Perfomance()
{
	INT64 ntime;
	QueryPerformanceCounter((LARGE_INTEGER*)&ntime);
	frametime = ntime - starttime;
	FPS = (int)(frencuency / frametime);
	starttime = ntime;
	PDH_FMT_COUNTERVALUE value;
	if(canReadCpu)
		if((lastSampleTime + 1000) < GetTickCount())
		{
			lastSampleTime = GetTickCount();
			PdhCollectQueryData(queryHandle);
			PdhGetFormattedCounterValue(counterHandle, PDH_FMT_LONG, NULL, &value);
			CPU = value.longValue;
		}
}

std::wstring GameEngine::ErrMsg()
{
	return TextMsg;
}

bool GameEngine::Initialize()
{
	//счетчик FPS
	QueryPerformanceFrequency((LARGE_INTEGER*)&frencuency);
	QueryPerformanceCounter((LARGE_INTEGER*)&starttime);
	//счетчик CPU нагрузки
	PDH_STATUS status;
	canReadCpu = true;
	status = PdhOpenQuery(NULL, 0, &queryHandle);
	if(status != ERROR_SUCCESS)
		canReadCpu = false;
	status = PdhAddCounter(queryHandle, L"\\\\Processor\\_Total\\% Processor Time", 0, &counterHandle);
	if(status != ERROR_SUCCESS)
		canReadCpu = false;
	lastSampleTime = GetTickCount();
	CPU = 0;
	return true;
}
