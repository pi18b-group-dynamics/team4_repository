#ifndef _AUDIOCORE_H_
#define _AUDIOCORE_H_

class AudioCore
{
public:
	AudioCore();
	AudioCore(const AudioCore&);
	~AudioCore();
	bool Init();
	void Destroy();
private:
};

#endif