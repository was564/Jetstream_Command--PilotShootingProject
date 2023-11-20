////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <string>

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Player = 0;
	m_EnemyAirCraft = 0;
	m_TextureShader = 0;
	m_Target = 0;
	m_SkyboxShader = 0;
	m_Ground_Mountain = 0;
	m_SkyboxShader = 0;
	m_Light = 0;
	m_LightShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);	// for cube model
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair model
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	
	// Create the model object.
	m_Player = new ModelClass;
	if(!m_Player)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Player->Initialize(m_D3D->GetDevice(), L"./data/PlayerModel.obj", L"./data/PlayerModel.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_EnemyAirCraft = new ModelClass;
	if (!m_EnemyAirCraft)
	{
		return false;
	}

	// Initialize the model object.
	result = m_EnemyAirCraft->Initialize(m_D3D->GetDevice(), L"./data/EnemyAirCraft.obj", L"./data/EnemyAirCraft.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_Target = new ModelClass;
	if (!m_Target)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Target->Initialize(m_D3D->GetDevice(), L"./data/Target.obj", L"./data/Target.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model object.
	m_Ground_Mountain = new ModelClass;
	if (!m_Ground_Mountain)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Ground_Mountain->Initialize(m_D3D->GetDevice(), L"./data/Mountain.obj", L"./data/Mountain.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	
	// Create the texture shader object.
	m_SkyboxShader = new SkyBoxShaderClass;
	if (!m_SkyboxShader)
	{
		return false;
	}
	

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.30f, 0.30f, 0.30f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, -1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(50.0f);


	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_SkyboxShader = new SkyBoxShaderClass;
	if (!m_SkyboxShader)
	{
		return false;
	}
	result = m_SkyboxShader->Initialize(m_D3D->GetDevice(), hwnd, m_Camera, m_D3D->GetSwapChain());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the skybox shader object.
	if (m_SkyboxShader)
	{
		m_SkyboxShader->Shutdown();
		delete m_SkyboxShader;
		m_SkyboxShader = 0;
	}

	// Release the model object.
	if(m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	// Release the model object.
	if (m_SkyboxShader)
	{
		m_SkyboxShader->Shutdown();
		delete m_SkyboxShader;
		m_SkyboxShader = 0;
	}

	// Release the model object.
	if (m_EnemyAirCraft)
	{
		m_EnemyAirCraft->Shutdown();
		delete m_EnemyAirCraft;
		m_EnemyAirCraft = 0;
	}

	// Release the model object.
	if (m_Target)
	{
		m_Target->Shutdown();
		delete m_Target;
		m_Target = 0;
	}

	// Release the model object.
	if (m_Ground_Mountain)
	{
		m_Ground_Mountain->Shutdown();
		delete m_Ground_Mountain;
		m_Ground_Mountain = 0;
	}

	// Release the model object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the model object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}



// how to use: mouseMovingValue (lx, ly), keyboard[ key ]
bool GraphicsClass::Frame(const std::pair<float, float>* mouseMovingValue, const BYTE* keyboardState)
{
	#define GetKeyDown(key) keyboardState[key] & 0x80

	bool result;

	static float speed = 0.3f * 0.01f; // 0.01f = 1 / average frame
	static float mouseSensibility = 0.1f;

	if (GetKeyDown(DIK_A)) m_Player->Rotate(0.0f, -1.0f, 0.0f);
	if (GetKeyDown(DIK_D)) m_Player->Rotate(0.0f, 1.0f, 0.0f);
	if (GetKeyDown(DIK_W)) m_Player->Rotate(-1.0f, 0.0f, 0.0f);
	if (GetKeyDown(DIK_S)) m_Player->Rotate(1.0f, 0.0f, 0.0f);
	float rotateZValue = 0.0f;
	if (GetKeyDown(DIK_Q)) rotateZValue = 1.0f;
	if (GetKeyDown(DIK_E)) rotateZValue = -1.0f;
	m_Camera->Move(m_Player->GetForward(), -speed);

	m_Player->Rotate(0.0f, 0.0f, rotateZValue);

	m_Camera->Rotate(
		mouseMovingValue->second * mouseSensibility, 
		mouseMovingValue->first * mouseSensibility,
		0.0f);

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	XMMATRIX playerMatrix, enemyAirCraftMatrix, targetMatrix, groundMatrix, boxMatrix;
	bool result;

	static float rotationYValue = 0.0f;

	rotationYValue += 0.01f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	
	result = m_SkyboxShader->Render(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	groundMatrix = worldMatrix;
	groundMatrix *= XMMatrixScaling(100.0f, 10.0f, 100.0f);
	groundMatrix *= XMMatrixTranslation(0.0f, -15.0f, 0.0f);
	m_Ground_Mountain->Render(m_D3D->GetDeviceContext());
	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Ground_Mountain->GetIndexCount(),
		groundMatrix, viewMatrix, projectionMatrix, m_Ground_Mountain->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Player->Render(m_D3D->GetDeviceContext());
	XMFLOAT3 playerRotation = m_Player->GetRotation();
	playerMatrix = worldMatrix;
	playerMatrix *= XMMatrixScaling(0.4f, 0.4f, 0.4f);
	playerMatrix *= XMMatrixRotationX(playerRotation.x);
	playerMatrix *= XMMatrixRotationY(playerRotation.y);
	playerMatrix *= XMMatrixRotationZ(playerRotation.z);
	playerMatrix *= XMMatrixTranslationFromVector(m_Camera->GetLookAtPosition());
	// Render the model using the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Player->GetIndexCount(),
		playerMatrix, viewMatrix, projectionMatrix, m_Player->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	m_EnemyAirCraft->Render(m_D3D->GetDeviceContext());
	enemyAirCraftMatrix = worldMatrix;
	enemyAirCraftMatrix *= XMMatrixTranslation(20.0f, 15.0f, 0.0f);
	// Render the model using the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_EnemyAirCraft->GetIndexCount(),
		enemyAirCraftMatrix, viewMatrix, projectionMatrix, m_EnemyAirCraft->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Target->Render(m_D3D->GetDeviceContext());
	targetMatrix = worldMatrix;
	targetMatrix = XMMatrixRotationZ(90.0f);
	targetMatrix = XMMatrixMultiply(targetMatrix, XMMatrixTranslation(-15.0f, 25.0f, 0.0f));
	
	// Render the model using the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Target->GetIndexCount(),
		targetMatrix, viewMatrix, projectionMatrix, m_Target->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Reference : https://stackoverflow.com/questions/17249434/how-to-dump-xmmatrix-member-value
	XMMATRIX mtxView = playerMatrix;
	XMFLOAT4X4 fView;
	XMStoreFloat4x4(&fView, mtxView);
	float x = fView._11;
	float y = fView._22;
	float z = fView._33;

	string sentence = 
		"CurrentPosition : (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	m_Text->UpdateSentence(0, sentence.c_str(), 100, 100, 1.0f, 1.0f, 1.0f, m_D3D->GetDeviceContext());
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}