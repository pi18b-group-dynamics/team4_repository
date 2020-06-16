#include "Audio.h"

Audio::Audio()
{
	m_DirectSound = 0;
	m_primaryBuffer = 0;
	m_secondaryBufferBack = 0;
	m_secondaryBufferEffect = 0;
}

Audio::~Audio()
{}

bool Audio::Init(HWND w)
{
	bool result;
	result = InitializeDirectSound(w);
	if(!result)
		return false;
	m_backcount = 0;
	m_effectcount = 0;
}

void Audio::Destrot()
{
	UnloadFiles();
	DestroyDirectSound();
}

void Audio::SetVolume(LONG v)
{
	m_volume = v;
}

LONG Audio::GetVolume()
{
	return m_volume;
}

bool Audio::LoadSound(LPCSTR fname, bool isBack)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;
	error = fopen_s(&filePtr, fname, "rb");
	if(error != 0)
		return false;
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if(count != 1)
		return false;
	if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
		return false;
	if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
		return false;
	if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
		return false;
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
		return false;
	if(waveFileHeader.numChannels != 2)
		return false;
	if(waveFileHeader.sampleRate != 44100)
		return false;
	if(waveFileHeader.bitsPerSample != 16)
		return false;
	if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
		return false;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if(FAILED(result))
		return false;
	IDirectSoundBuffer8** tb;
	if(isBack)
	{
		tb = new IDirectSoundBuffer8 * [m_backcount++];
		for(int i = 0; i < m_backcount - 1; i++)
			tb[i] = m_secondaryBufferBack[i];
		result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)(&(tb[m_backcount-1])));
		m_secondaryBufferBack = tb;
	}
	else
	{
		tb = new IDirectSoundBuffer8 * [m_effectcount++];
		for(int i = 0; i < m_effectcount - 1; i++)
			tb[i] = m_secondaryBufferEffect[i];
		result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)(&(tb[m_effectcount-1])));
		m_secondaryBufferEffect = tb;
	}
	if(FAILED(result))
	{
		if(isBack)
			m_backcount--;
		else
			m_effectcount--;
		return false;
	}
	tempBuffer->Release();
	tempBuffer = 0;
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);
	waveData = new unsigned char[waveFileHeader.dataSize];
	if(!waveData)
		return false;
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if(count != waveFileHeader.dataSize)
		return false;
	error = fclose(filePtr);
	if(error != 0)
		return false;
	result = tb[(isBack) ? (m_backcount - 1) : (m_effectcount - 1)]->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		if(isBack)
			m_backcount--;
		else
			m_effectcount--;
		return false;
	}
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);
	result = tb[(isBack) ? (m_backcount - 1) : (m_effectcount - 1)]->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		if(isBack)
			m_backcount--;
		else
			m_effectcount--;
		return false;
	}
	delete[] waveData;
	waveData = 0;
	return true;
}

void Audio::PlayBack(int i)
{
	m_secondaryBufferBack[i - 1]->SetCurrentPosition(0);
	m_secondaryBufferBack[i - 1]->SetVolume(-(4900 - m_volume*700));
	m_secondaryBufferBack[i - 1]->Play(0, 0, DSBPLAY_LOOPING);
	m_playnow = i;
}

void Audio::PlayEffect(int i)
{
	m_secondaryBufferEffect[i - 1]->SetVolume(-(4900 - m_volume * 700));
	m_secondaryBufferEffect[i - 1]->Play(0, 0, 0);
}

void Audio::Stop(int i)
{
	m_secondaryBufferBack[i - 1]->Stop();
	m_playnow = 0;
}

int Audio::GetBackCount()
{
	return m_backcount;
}

int Audio::GetEffeckCount()
{
	return m_effectcount;
}

int Audio::PlayNow()
{
	return m_playnow;
}

bool Audio::InitializeDirectSound(HWND w)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if(FAILED(result))
		return false;
	result = m_DirectSound->SetCooperativeLevel(w, DSSCL_PRIORITY);
	if(FAILED(result))
		return false;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if(FAILED(result))
		return false;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if(FAILED(result))
		return false;
	return true;
}

void Audio::DestroyDirectSound()
{
	if(m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}
	if(m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}
	return;
}

void Audio::UnloadFiles()
{
	for(int i = 0; i < m_backcount; i++)
		m_secondaryBufferBack[i]->Release();
	delete m_secondaryBufferBack;
	m_secondaryBufferBack = 0;
	for(int i = 0; i < m_effectcount; i++)
		m_secondaryBufferEffect[i]->Release();
	delete m_secondaryBufferEffect;
	m_secondaryBufferEffect = 0;
}
