#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

#include "Game.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

struct WaveHeaderType
{
	char chunkId[4];
	unsigned long chunkSize;
	char format[4];
	char subChunkId[4];
	unsigned long subChunkSize;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long bytesPerSecond;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char dataChunkId[4];
	unsigned long dataSize;
};

class AudioCore
{
private:
	IDirectSoundBuffer8** SoundBuffers;
	IDirectSound8* SoundDevice;
	IDirectSoundBuffer8* primaryBuffer;
	LONG BackgroundVolume;
	LONG ForwardVolume;
	int BackgroundIndex;
public:
	AudioCore(HWND wnd);
	~AudioCore();
	void PlayBackground(int SoundIndex);
	void PlayForward(int SoundIndex);
	void SetBackgroundVolume(int Volume); // - 10000; 0;
	void SetForwardVolume(int Volume);
	void StopBackground();
	void GetBackgroundIndex();
};