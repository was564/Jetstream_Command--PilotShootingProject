////////////////////////////////////////////////////////////////////////////////
// Filename: d3dclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////
// INCLUDES //
//////////////
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <directxmath.h>

#include "AlignedAllocationPolicy.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: D3DClass
////////////////////////////////////////////////////////////////////////////////
class D3DClass : public AlignedAllocationPolicy<16>
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	void TurnOnCullNone();
	void TurnOffCullNone();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	ID3D11DepthStencilState* m_depthDisabledStencilState;

	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;

	ID3D11RasterizerState* m_RasterizerStateCullNone;
	ID3D11DepthStencilState* m_DepthStencilStateLessEqual;
};

#endif