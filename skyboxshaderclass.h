#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: skyboxshaderclass.h
// The TextureShaderClass is just an updated version of the ColorShaderClass from 
// the previous tutorial. This class will be used to draw the 3D models using vertex 
// and pixel shaders.
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYBOXSHADERCLASS_H_
#define _SKYBOXSHADERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <dinput.h>

#include <vector>
#include <fstream>

#include "cameraclass.h"

using namespace std;
using namespace DirectX;


struct Vertex	//Overloaded Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: SkyShaderClass
////////////////////////////////////////////////////////////////////////////////
class SkyBoxShaderClass
{
private:
	struct cbPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX World;
	};

public:
	SkyBoxShaderClass();
	SkyBoxShaderClass(const SkyBoxShaderClass&);
	~SkyBoxShaderClass();

	bool Initialize(ID3D11Device*, HWND, CameraClass*, IDXGISwapChain*);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	bool InitD2D_D3D101_DWrite(IDXGIAdapter1* Adapter);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(ID3D11DeviceContext*);

private:
	ID3D11VertexShader* m_SKYMAP_VS;
	ID3D11PixelShader* m_SKYMAP_PS;
	ID3D10Blob* m_SKYMAP_VS_Buffer;
	ID3D10Blob* m_SKYMAP_PS_Buffer;
	ID3D11ShaderResourceView* m_smrv;

	bool CreateSphere(int, int, ID3D11Device*);

	ID3D11Texture2D* m_Texture;

	int NumSphereVertices;
	int NumSphereFaces;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	ID3D11Buffer* m_sphereIndexBuffer;
	ID3D11Buffer* m_sphereVertBuffer;
	ID3D11Buffer* m_cbPerObjectBuffer;
	ID3D11SamplerState* m_CubesTexSamplerState;
	ID3D11RasterizerState* m_CCWcullMode;
	ID3D11RasterizerState* m_CWcullMode;
	ID3D11RasterizerState* m_RSCullNone;
	ID3D11DepthStencilState* m_DSLessEqual;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RenderTargetView* m_renderTargetView;
	IDXGISwapChain* m_swapChain;
	ID3D11Texture2D* m_BackBuffer11;
	// ID3D11InputLayout* m_layout;
	// ID3D11Buffer* m_matrixBuffer;
	// ID3D11SamplerState* m_sampleState;

	CameraClass* m_Camera;
};

#endif