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
	m_CameraManager = 0;
    m_PlayerManager = 0;
	m_Player = 0;
	m_EnemyAirCraft = 0;
	m_TextureShader = 0;
	m_Target = 0;
	m_SkyboxShader = 0;
	m_Ground_Mountain = 0;
	m_SkyboxShader = 0;
	m_Light = 0;
	m_LightShader = 0;
    m_Sound = 0;
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

    m_ScreenWidth = screenWidth;
    m_ScreentHeight = screenHeight;

    m_RenderObjectList.resize(ShaderName::Size);

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

    // Create the model object.
    m_Player = new ModelClass;
    if (!m_Player)
    {
        return false;
    }

    // Initialize the model object.
    result = m_Player->Initialize(m_D3D->GetDevice(), L"./data/PlayerModel.obj", L"./data/PlayerModel.dds");
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }

    m_Player->SetScale(0.4f, 0.4f, 0.4f);

	// Create the camera object.
	m_CameraManager = new CameraManagerClass;
	if(!m_CameraManager)
	{
		return false;
	}
    
    result = m_CameraManager->Initialize(m_Player, XMFLOAT3(0.0f, -2.0f, 0.0f));
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }
    m_CameraManager->GetCameraInstance()->GetViewMatrix(baseViewMatrix);
	
    m_PlayerManager = new PlayerManagerClass;
    if (!m_PlayerManager)
    {
        return false;
    }

    result = m_PlayerManager->Initialize(m_D3D->GetDevice(), m_Player, this);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }

    m_EnemyManager = new EnemyManagerClass;
    if (!m_EnemyManager)
    {
        return false;
    }

    result = m_EnemyManager->Initialize(m_D3D->GetDevice(), this, 5);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }

<<<<<<< Updated upstream
=======
    m_InputManager = new InputManagerClass;
    if (!m_InputManager)
    {
        return false;
    }

    result = m_InputManager->Initialize(m_PlayerManager, m_CameraManager);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize InputManager.", L"Error", MB_OK);
        return false;
    }

>>>>>>> Stashed changes
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
    m_Cube->SetPosition(5.0f, 5.0f, 5.0f);
	

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
    m_EnemyAirCraft->SetPosition(20.0f, 15.0f, 0.0f);

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
    m_Target->SetPosition(-15.0f, 25.0f, 0.0f);

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
    m_Ground_Mountain->SetScale(40.0f, 10.0f, 40.0f);
    m_Ground_Mountain->SetPosition(0.0f, -45.0f, 0.0f);

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
	result = m_SkyboxShader->Initialize(m_D3D->GetDevice(), hwnd, baseViewMatrix);
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
    
    // Create the bitmap object.
    m_Aim = new BitmapClass;
    if (!m_Aim)
    {
        return false;
    }

    // Initialize the bitmap object.
    result = m_Aim->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, L"./data/aim.dds", 300, 300, baseViewMatrix);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
        return false;
    }

    /*
    // Create the sound object.
    m_Sound = new SoundClass;
    if (!m_Sound)
    {
        return false;
    }

    // Initialize the sound object.
    result = m_Sound->Initialize(hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
        return false;
    }
    */

    m_RenderObjectList[ShaderName::LightShader].insert(m_Player);
    //m_RenderObjectList[ShaderName::LightShader].insert(m_EnemyAirCraft);
    //m_RenderObjectList[ShaderName::LightShader].insert(m_Target);
    //m_RenderObjectList[ShaderName::FireShader].insert(m_Cube);
    m_RenderObjectList[ShaderName::FogShader].insert(m_Ground_Mountain);
    //m_RenderObjectList[ShaderName::ParticleShader].insert(m_ParticleSystem);


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
    if (m_InputManager)
    {
        m_InputManager->Shutdown();
        delete m_InputManager;
        m_InputManager = 0;
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
	if(m_CameraManager)
	{
		delete m_CameraManager;
        m_CameraManager = 0;
	}

    // Release the camera object.
    if (m_PlayerManager)
    {
        m_PlayerManager->Shutdown();
        delete m_PlayerManager;
        m_PlayerManager = 0;
    }

    if (m_UIManager)
    {
        delete m_PlayerManager;
        m_PlayerManager = 0;
    }

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

    /*
    // Release the sound object.
    if (m_Sound)
    {
        m_Sound->Shutdown();
        delete m_Sound;
        m_Sound = 0;
    }
    */
	return;
}



// how to use: mouseMovingValue (lx, ly), keyboard[ key ]
bool GraphicsClass::Frame(const DIMOUSESTATE& mouseState, const BYTE* keyboardState, 
	int fps, int cpu, float frameTime)
{

	bool result;

    // frame

<<<<<<< Updated upstream
    m_PlayerManager->Frame(mouseState, keyboardState, frameTime, m_D3D->GetDeviceContext());
    m_CameraManager->Frame(mouseState, keyboardState);

=======
    m_InputManager->Frame(mouseState, keyboardState);

    m_PlayerManager->Frame(frameTime, m_D3D->GetDeviceContext());
    m_CameraManager->Frame(mouseState);

>>>>>>> Stashed changes
    m_EnemyManager->Frame(m_PlayerManager->GetMissile());
    m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

    // text
    XMFLOAT3 playerPosition = m_Player->GetPosition();

    // Reference : https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
    stringstream ss;
    ss << std::fixed << std::setprecision(2) << playerPosition.x << " " << playerPosition.y << " " << playerPosition.z;
    string positionString[3];
    string token;
    for (int i = 0; ss >> token; i++) {
        positionString[i] = token;
    }
    ss.clear();

    string sentence =
        "CurrentPosition : (" + positionString[0] + ", " + positionString[1] + ", " + positionString[2] + ")";
    result = m_Text->UpdateSentence(0, sentence.c_str(), 100, 100, 1.0f, 1.0f, 1.0f, m_D3D->GetDeviceContext());
    if (!result)
    {
        return false;
    }

    XMFLOAT3 playerRotation = m_Player->GetRotation();
    ss << std::fixed << std::setprecision(2) << playerRotation.x << " " << playerRotation.y << " " << playerRotation.z;
    string rotationString[3];
    for (int i = 0; ss >> token; i++) {
        rotationString[i] = token;
    }
    ss.clear();

    sentence =
        "CurrentRotation : (" + rotationString[0] + ", " + rotationString[1] + ", " + rotationString[2] + ")";
    result = m_Text->UpdateSentence(1, sentence.c_str(), 100, 130, 1.0f, 1.0f, 1.0f, m_D3D->GetDeviceContext());
    if (!result)
    {
        return false;
    }

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

void GraphicsClass::AddRenderObject(ShaderName shader, ObjectClass* object)
{
    m_RenderObjectList[shader].insert(object);
}

bool GraphicsClass::RemoveRenderObject(ObjectClass* object)
{
    for (set<ObjectClass*>& objectSet : m_RenderObjectList)
    {
        set<ObjectClass*>::iterator iter = objectSet.find(object);
        if (iter == objectSet.end()) continue;
        else
        {
            objectSet.erase(iter);
            return true;
        }
    }

    return false;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
    XMFLOAT3 cameraPosition, actualCameraPosition;
	bool result;

	static float rotationYValue = 0.0f;

	rotationYValue += 0.01f;

	int polygonCount = 0;
	int objectCount = 0;

    // Set the color of the fog to grey.
    float Red = 0.4f;
    float Green = 0.4f;
    float Blue = 1.0f;


    cameraPosition = m_CameraManager->GetCameraInstance()->GetPosition();

    actualCameraPosition = m_CameraManager->GetCameraInstance()->GetActualPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(Red, Green, Blue, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_CameraManager->GetCameraInstance()->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
    m_CameraManager->GetCameraInstance()->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	m_D3D->TurnOnCullNone();
	/*
	result = m_SkyboxShader->Render(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, actualCameraPosition);
	if (!result)
	{
		return false;
	}
	*/
	m_D3D->TurnOffCullNone();
    

    // Set the start and end of the fog.
    float fogStart = 0.0f;
    float fogEnd = 100.0f;

    for (ObjectClass* model : m_RenderObjectList[ShaderName::FogShader]) 
    {
        XMFLOAT3 modelScale = model->GetScale();
        XMFLOAT3 modelRotation = model->GetRotation();
        XMFLOAT3 modelPosition = model->GetPosition();

        XMMATRIX modelMatrix = worldMatrix;
        modelMatrix *= XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
        modelMatrix *= XMMatrixRotationX(modelRotation.x * 0.0174532925f);
        modelMatrix *= XMMatrixRotationY(modelRotation.y * 0.0174532925f);
        modelMatrix *= XMMatrixRotationZ(modelRotation.z * 0.0174532925f);
        modelMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);
        model->Render(m_D3D->GetDeviceContext());
        // Render the square model using the fire shader.
        result = m_FogShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), modelMatrix, viewMatrix, projectionMatrix,
            model->GetTexture(), fogStart, fogEnd);
        if (!result)
        {
            return false;
        }
        polygonCount += model->GetIndexCount();
        objectCount += 1;
    }

    for (ObjectClass* model : m_RenderObjectList[ShaderName::LightShader])
    {
        XMFLOAT3 modelScale = model->GetScale();
        XMFLOAT3 modelRotation = model->GetRotation();
        XMFLOAT3 modelPosition = model->GetPosition();

        XMMATRIX modelMatrix = worldMatrix;
        modelMatrix *= XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
        modelMatrix *= XMMatrixRotationX(modelRotation.x * 0.0174532925f);
        modelMatrix *= XMMatrixRotationY(modelRotation.y * 0.0174532925f);
        modelMatrix *= XMMatrixRotationZ(modelRotation.z * 0.0174532925f);
        modelMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);
        model->Render(m_D3D->GetDeviceContext());
        // Render the square model using the fire shader.
        result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
            modelMatrix, viewMatrix, projectionMatrix, model->GetTexture(),
            m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
            cameraPosition, m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
        if (!result)
        {
            return false;
        }
        polygonCount += model->GetIndexCount();
        objectCount += 1;
    }
	

	m_D3D->TurnOnAlphaBlending();

    


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

    for (ObjectClass* model : m_RenderObjectList[ShaderName::FireShader]) {
        XMFLOAT3 modelScale = model->GetScale();
        XMFLOAT3 modelRotation = model->GetRotation();
        XMFLOAT3 modelPosition = model->GetPosition();

        XMMATRIX modelMatrix = worldMatrix;
        modelMatrix *= XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
        modelMatrix *= XMMatrixRotationX(modelRotation.x * 0.0174532925f);
        modelMatrix *= XMMatrixRotationY(modelRotation.y * 0.0174532925f);
        modelMatrix *= XMMatrixRotationZ(modelRotation.z * 0.0174532925f);
        modelMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);
        model->Render(m_D3D->GetDeviceContext());
        // Render the square model using the fire shader.
        result = m_FireShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), modelMatrix, viewMatrix, projectionMatrix,
            model->GetTexture1(), model->GetTexture2(), model->GetTexture3(), frameTime, scrollSpeeds,
            scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
        if (!result)
        {
            return false;
        }
        polygonCount += model->GetIndexCount();
        objectCount += 1;
    }

    // for billboarding
    cameraPosition = m_CameraManager->GetCameraInstance()->GetActualPosition();

    for (ObjectClass* model : m_RenderObjectList[ShaderName::ParticleShader])
    {
        XMFLOAT3 modelScale = model->GetScale();
        XMFLOAT3 modelPosition = model->GetPosition();

        // 아크 탄젠트 함수를 사용하여 현재 카메라 위치를 향하도록 빌보드 모델에 적용해야하는 회전을 계산합니다.
        double angle = atan2(modelPosition.x - cameraPosition.x, modelPosition.z - cameraPosition.z) * (180.0 / XM_PI);

        // 회전을 라디안으로 변환합니다.
        float rotation = (float)angle * 0.0174532925f;

        XMMATRIX modelMatrix = worldMatrix;
        modelMatrix *= XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
        modelMatrix *= XMMatrixRotationY(rotation);
        modelMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);
        model->Render(m_D3D->GetDeviceContext());

        result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), modelMatrix, viewMatrix, projectionMatrix,
            model->GetTexture());
        if (!result)
        {
            return false;
        }
        polygonCount += model->GetIndexCount();
        objectCount += 1;
    }

    // Turn off alpha blending.
    m_D3D->TurnOffAlphaBlending();

    // Turn off the Z buffer to begin all 2D rendering.
    m_D3D->TurnZBufferOff();

    for (ObjectClass* model : m_RenderObjectList[ShaderName::TextureShader])
    {
        XMFLOAT3 modelScale = model->GetScale();
        
        XMMATRIX modelMatrix = worldMatrix;
        modelMatrix *= XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
        model->Render(m_D3D->GetDeviceContext());

        result = m_TextureShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), modelMatrix, viewMatrix, projectionMatrix,
            model->GetTexture());
        if (!result)
        {
            return false;
        }
        polygonCount += model->GetIndexCount();
        objectCount += 1;
    }

    // Turn on the alpha blending before rendering the text.
    m_D3D->TurnOnAlphaBlending();

    if (m_CameraManager->GetMode() == CameraManagerClass::CameraMode::AimingMode)
    {
        result = m_Aim->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
        if (!result)
        {
            return false;
        }
    }
    

    // Render the text strings.
    result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
    if (!result)
    {
        return false;
    }
    polygonCount += m_Text->GetTotalSentenceIndexCount();
    m_Text->SetPolygons(polygonCount, m_D3D->GetDeviceContext());
    m_Text->SetObjects(objectCount, m_D3D->GetDeviceContext());

    // Turn the Z buffer back on now that all 2D rendering has completed.
    m_D3D->TurnZBufferOn();
    // Turn off alpha blending after rendering the text.
    m_D3D->TurnOffAlphaBlending();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}