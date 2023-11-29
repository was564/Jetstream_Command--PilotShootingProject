////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "skyboxshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "fogshaderclass.h"
#include <dinput.h>


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
const XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(const std::pair<float, float>*, const BYTE*, int, int, float);

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Player;
	ModelClass* m_EnemyAirCraft;
	ModelClass* m_Target;
	ModelClass* m_Ground_Mountain;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;

	SkyBoxShaderClass* m_SkyboxShader;
	FogShaderClass* m_FogShader;

	TextClass* m_Text;
};

#endif