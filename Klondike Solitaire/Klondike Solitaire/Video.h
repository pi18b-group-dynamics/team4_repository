#pragma once

#include <D3D10.h>
#include <D3DX10.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

class Video
{
public:
	Video();
	~Video();
	bool Init(HWND w, int ws, int hs);
	bool Frame();
	void Destroy();
	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void TurnZBufferOn();
	void TurnZBufferOff();
	void PrintText(LPCSTR str,LPRECT r, UINT f, D3DXCOLOR c);
private:
	bool InitD3Device(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
		float screenDepth, float screenNear);
	bool InitCamera();

	bool m_vsync_enabled;
	ID3D10Device* m_device;
	IDXGISwapChain* m_swapChain;
	ID3D10RenderTargetView* m_renderTargetView;
	ID3D10Texture2D* m_depthStencilBuffer;
	ID3D10DepthStencilState* m_depthStencilState;
	ID3D10DepthStencilView* m_depthStencilView;
	ID3D10RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	ID3D10DepthStencilState* m_depthDisabledStencilState;
	D3DXMATRIX m_viewMatrix;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	ID3DX10Font* m_font;

};