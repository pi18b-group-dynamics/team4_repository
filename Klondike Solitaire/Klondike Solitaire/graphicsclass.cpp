#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Text = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{}

GraphicsClass::~GraphicsClass()
{}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D.", "Error", MB_OK);
		return false;
	}
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}
	result = m_Text->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, "Could not initialize the text object.", "Error", MB_OK);
		return false;
	}
	return true;
}

void GraphicsClass::Shutdown()
{
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}

void GraphicsClass::Frame()
{
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	return;
}

bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->Render();
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->TurnZBufferOff();
	m_Text->Render(m_D3D->GetDevice(), worldMatrix, orthoMatrix);
	m_D3D->TurnZBufferOn();
	m_D3D->EndScene();
	return true;
}