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
#include "fireshaderclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
#include "cameramanagerclass.h"
#include "playermanagerclass.h"
#include "uimanagerclass.h"
#include "objectclass.h"
#include "bitmapclass.h"
#include "enemymanagerclass.h"
#include "soundclass.h"
#include "inputmanagerclass.h"
#include <dinput.h>
#include <set>
#include <map>


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
class GraphicsClass // GameManager
{
public:
    enum ShaderName
    {
        SkyBoxShader = 0,
        TextureShader,
        FogShader,
        FireShader,
        LightShader,
        ParticleShader,
        Size
    };

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(const DIMOUSESTATE&, const BYTE*, int, int, float);

    void AddRenderObject(ShaderName, ObjectClass*);
    bool RemoveRenderObject(ObjectClass*);

private:
	bool Render();

private:
	D3DClass* m_D3D;
    CameraManagerClass* m_CameraManager;
    PlayerManagerClass* m_PlayerManager;
    UIManagerClass* m_UIManager;
    EnemyManagerClass* m_EnemyManager;

    InputManagerClass* m_InputManager;

    LightClass* m_Light;
    
    ModelClass* m_Player;
    ModelClass* m_EnemyAirCraft;
	ModelClass* m_Target;
	ModelClass* m_Ground_Mountain;
	ModelClass* m_Cube;
    BitmapClass* m_Aim;
    ParticleSystemClass* m_ParticleSystem;

	LightShaderClass* m_LightShader;

	TextureShaderClass* m_TextureShader;

	SkyBoxShaderClass* m_SkyboxShader;
	FogShaderClass* m_FogShader;
	FireShaderClass* m_FireShader;

    ParticleShaderClass* m_ParticleShader;
    
    // m_RenderObjectList[ ShaderName ][ objectIndex ]
    vector<set<ObjectClass*>> m_RenderObjectList;

	TextClass* m_Text;

    SoundClass* m_Sound;

    float m_ScreenWidth, m_ScreentHeight;
};

#endif