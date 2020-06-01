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
	std::wstring TextMsg;//��������� �� ������
	VideoCore* Video;//����������� ������
	InputCore* Input;//���������� �����
	AudioCore* Audio;//�������� ����������
	ShellCore* Shell;//���������������
	INT64 frencuency;//�������� ���������� � ��������/���
	INT64 starttime;//����� ���������� ������
	INT64 frametime;//������������ ��������� ������
	int FPS;//���-�� ������ � ���
	bool canReadCpu;//������������ �� ��������� ������ ������������������
	HQUERY queryHandle;//��������� �� ������ ������������������
	HCOUNTER counterHandle;//��������� �� ������� ������������������
	unsigned long lastSampleTime;//����� ���������� ������� ������������������
	INT64 CPU;//�������� �� ��������� � ���������
	HWND window;//���������� ����
};
#endif