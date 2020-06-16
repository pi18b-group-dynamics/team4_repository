#pragma once

#include <dsound.h>
#include <stdio.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

class Audio
{
public:
	Audio();
	~Audio();
	bool Init(HWND w);
	void Destrot();
	void SetVolume(LONG v);
	LONG GetVolume();
	bool LoadSound(LPCSTR fname, bool isBack);
	void PlayBack(int i);
	void PlayEffect(int i);
	void Stop(int i);
	int GetBackCount();
	int GetEffeckCount();
	int PlayNow();
private:
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

	bool InitializeDirectSound(HWND w);
	void DestroyDirectSound();
	void UnloadFiles();

	int m_backcount;
	int m_effectcount;
	LONG m_volume;
	int m_playnow;

	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8** m_secondaryBufferBack;
	IDirectSoundBuffer8** m_secondaryBufferEffect;
};