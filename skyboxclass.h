////////////////////////////////////////////////////////////////////////////////
// Filename: skyboxclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYBOXCLASS_H_
#define _SKYBOXCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class SkyBoxClass
{
public:

	SkyBoxClass();
	SkyBoxClass(const SkyBoxClass&);
	~SkyBoxClass();

	bool Initialize(ID3D11Device*, const WCHAR*);
	void Shutdown();
	
	ID3D11Texture2D* GetTexture();

private:
	bool CreateSphere(int, int, ID3D11Device*);
	
	ID3D11Buffer* m_sphereIndexBuffer;
	ID3D11Texture2D* m_Texture;

	int NumSphereVertices;
	int NumSphereFaces;

	XMMATRIX sphereWorld;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
};




#endif