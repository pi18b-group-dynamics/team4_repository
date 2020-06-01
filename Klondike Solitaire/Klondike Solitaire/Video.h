#ifndef _VIDEOCORE_H_
#define _VIDEOCORE_H_

#include <d3d10.h>
#include <d3dx10.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

class VideoCore
{
public:
	VideoCore();
	VideoCore(const VideoCore&);
	~VideoCore();
	bool Init(int W, int H, HWND* wnd);
	void Destroy();
	HWND GetWindow(int W, int H);
private:

};
#endif