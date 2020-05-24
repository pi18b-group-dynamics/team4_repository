#ifndef _VIDEOCORE_H_
#define _VIDEOCORE_H_

class VideoCore
{
public:
	VideoCore();
	VideoCore(const VideoCore&);
	~VideoCore();
	bool Init();
	void Destroy();
private:

};
#endif