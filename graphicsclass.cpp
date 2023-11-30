////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <string>
#include <sstream>
#include <iomanip>

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

	
	m_Cube = new ModelClass;
	if (!m_Cube)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Cube->Initialize(m_D3D->GetDevice(), L"./data/cube.obj", L"./data/Mountain.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

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


    // Set the initial position of the camera.
    m_Camera->SetPosition(0.0f, -2.0f, 0.0f);
    m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

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
	result = m_SkyboxShader->Initialize(m_D3D->GetDevice(), hwnd, m_Camera);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	m_FogShader = new FogShaderClass;
	if (!m_FogShader)
	{
		return false;
	}
	// Initialize the fog shader object.
	result = m_FogShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fog shader object.", L"Error", MB_OK);
		return false;
	}

    m_FireShader = new FireShaderClass;
    if (!m_FireShader)
    {
        return false;
    }
    // Initialize the fog shader object.
    result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
        return false;
    }

    // Create the particle shader object.
    m_ParticleShader = new ParticleShaderClass;
    if (!m_ParticleShader)
    {
        return false;
    }

    // Initialize the particle shader object.
    result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
        return false;
    }

    // Create the particle system object.
    m_ParticleSystem = new ParticleSystemClass;
    if (!m_ParticleSystem)
    {
        return false;
    }

    // Initialize the particle system object.
    result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"./data/star.dds");
    if (!result)
    {
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
	if(m_ParticleSystem)
	{
        m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
        m_ParticleSystem = 0;
	}

    // Release the texture shader object.
    if (m_ParticleShader)
    {
        m_ParticleShader->Shutdown();
        delete m_ParticleShader;
        m_ParticleShader = 0;
    }

    // Release the texture shader object.
    if (m_TextureShader)
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

	// Release the skybox shader object.
	if (m_FogShader)
	{
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}


	// Release the model object.
	if(m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
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
bool GraphicsClass::Frame(const std::pair<float, float>* mouseMovingValue, const BYTE* keyboardState, 
	int fps, int cpu, float frameTime)
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

    m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

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
	XMMATRIX playerMatrix, enemyAirCraftMatrix, targetMatrix, groundMatrix, burnedCubeMatrix, particleMatrix;
    XMFLOAT3 particlePosition, cameraPosition;
	bool result;

	static float rotationYValue = 0.0f;

	rotationYValue += 0.01f;

	int polygonCount = 0;
	int objectCount = 0;
	float fogColor, fogStart, fogEnd;
	// Set the color of the fog to grey.
	fogColor = 0.2f;

	// Set the start and end of the fog.
	fogStart = 0.0f;
	fogEnd = 100.0f;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(fogColor, fogColor, fogColor, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	m_D3D->TurnOnCullNone();
	/*
	result = m_SkyboxShader->Render(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	*/
	m_D3D->TurnOffCullNone();

	groundMatrix = worldMatrix;
	groundMatrix *= XMMatrixScaling(30.0f, 10.0f, 30.0f);
	groundMatrix *= XMMatrixTranslation(0.0f, -40.0f, 0.0f);
	m_Ground_Mountain->Render(m_D3D->GetDeviceContext());

	result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Ground_Mountain->GetIndexCount(), groundMatrix, viewMatrix, projectionMatrix,
		m_Ground_Mountain->GetTexture(), fogStart, fogEnd);
	if (!result)
	{
		return false;
	}
	polygonCount += m_Ground_Mountain->GetIndexCount();
	objectCount += 1;
	// Render the model using the texture shader.
	/*
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Ground_Mountain->GetIndexCount(),
		groundMatrix, viewMatrix, projectionMatrix, m_Ground_Mountain->GetTexture());
	if (!result)
	{
		return false;
	}
	*/

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
	polygonCount += m_Player->GetIndexCount();
	objectCount += 1;

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
	polygonCount += m_EnemyAirCraft->GetIndexCount();
	objectCount += 1;

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
	polygonCount += m_Target->GetIndexCount();
	objectCount += 1;

	// FireShader
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = XMFLOAT3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	m_D3D->TurnOnAlphaBlending();


    burnedCubeMatrix = worldMatrix;
    burnedCubeMatrix *= XMMatrixTranslation(5.0f, 5.0f, 5.0f);
    m_Cube->Render(m_D3D->GetDeviceContext());

    // Render the square model using the fire shader.
    result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), burnedCubeMatrix, viewMatrix, projectionMatrix,
        m_Cube->GetTexture1(), m_Cube->GetTexture2(), m_Cube->GetTexture3(), frameTime, scrollSpeeds,
        scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
    if (!result)
    {
        return false;
    }
    polygonCount += m_Cube->GetIndexCount();
    objectCount += 1;

    m_ParticleSystem->Render(m_D3D->GetDeviceContext());

    // for billboarding
    cameraPosition = m_Camera->GetActualPosition();
    particlePosition = XMFLOAT3(0.0f, 1.0f, 0.0f);
    // 아크 탄젠트 함수를 사용하여 현재 카메라 위치를 향하도록 빌보드 모델에 적용해야하는 회전을 계산합니다.
    double angle = atan2(particlePosition.x - cameraPosition.x, particlePosition.z - cameraPosition.z) * (180.0 / XM_PI);

    // 회전을 라디안으로 변환합니다.
    float rotation = (float)angle * 0.0174532925f;

    particleMatrix = worldMatrix;
    particleMatrix *= XMMatrixRotationY(rotation);
    particleMatrix *= XMMatrixTranslationFromVector(XMLoadFloat3(&particlePosition));
    // Render the model using the texture shader.
    result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleMatrix, viewMatrix, projectionMatrix,
        m_ParticleSystem->GetTexture());
    if (!result)
    {
        return false;
    }
    polygonCount += m_ParticleSystem->GetIndexCount();
    objectCount += 1;

    // Turn off alpha blending.
    m_D3D->TurnOffAlphaBlending();

    // Turn off the Z buffer to begin all 2D rendering.
    m_D3D->TurnZBufferOff();
    // Turn on the alpha blending before rendering the text.
    m_D3D->TurnOnAlphaBlending();

    // Reference : https://stackoverflow.com/questions/17249434/how-to-dump-xmmatrix-member-value
    XMMATRIX mtxView = playerMatrix;
    XMFLOAT4X4 fView;
    XMStoreFloat4x4(&fView, mtxView);
    float x = fView._41;
    float y = fView._42;
    float z = fView._43;

    // Reference : https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
    stringstream ss;
    ss << std::fixed << std::setprecision(2) << x << " " << y << " " << z;
    string position[3];
    string token;
    for (int i = 0; ss >> token; i++) {
        position[i] = token;
    }

    string sentence =
        "CurrentPosition : (" + position[0] + ", " + position[1] + ", " + position[2] + ")";
    result = m_Text->UpdateSentence(0, sentence.c_str(), 100, 100, 1.0f, 1.0f, 1.0f, m_D3D->GetDeviceContext());
    if (!result)
    {
        return false;
    }

    polygonCount += m_Text->GetTotalSentenceIndexCount();
    m_Text->SetPolygons(polygonCount, m_D3D->GetDeviceContext());
    m_Text->SetObjects(objectCount, m_D3D->GetDeviceContext());

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