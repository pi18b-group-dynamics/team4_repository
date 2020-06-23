#pragma once
#include <fstream>
using namespace std;

#include "textureclass.h"

class FontClass
{
private:
	struct FontType
	{
		float left, right, top, button;
		int size;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D10Device*, const char*, const CHAR*);
	void Shutdown();

	ID3D10ShaderResourceView* GetTexture();

	void BuildVertexArray(void*, const char*, float, float);

private:
	bool LoadFontData(const char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D10Device*, const CHAR*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	TextureClass* m_Texture;
};