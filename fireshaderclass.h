////////////////////////////////////////////////////////////////////////////////
// Filename: fireshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FIRESHADERCLASS_H_
#define _FIRESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "shaderinterface.h"

#include <fstream>

using namespace std;
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: FireShaderClass
////////////////////////////////////////////////////////////////////////////////
class FireShaderClass : public IShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct NoiseBufferType
	{
		float frameTime;
		XMFLOAT3 scrollSpeeds;
		XMFLOAT3 scales;
		float padding;
	};

	struct DistortionBufferType
	{
		XMFLOAT2 distortion1;
		XMFLOAT2 distortion2;
		XMFLOAT2 distortion3;
		float distortionScale;
		float distortionBias;
	};

public:
	FireShaderClass();
	FireShaderClass(const FireShaderClass&);
	~FireShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
				ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT3, XMFLOAT2, XMFLOAT2, XMFLOAT2, float, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
							 ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, XMFLOAT3, XMFLOAT3, XMFLOAT2,
							XMFLOAT2, XMFLOAT2, float, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_noiseBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* m_sampleState2;
	ID3D11Buffer* m_distortionBuffer;
};

#endif