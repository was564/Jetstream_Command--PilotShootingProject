#include "playermanagerclass.h"
#include "graphicsclass.h"

<<<<<<< Updated upstream
PlayerManagerClass::PlayerManagerClass()
{
    m_Player = 0;
    m_Missile = 0;
    m_IsFired = false;
=======

PlayerManagerClass::PlayerManagerClass()
{
    m_Player = 0;
    m_Graphics = 0;
    m_Missile = 0;
>>>>>>> Stashed changes
}

PlayerManagerClass::~PlayerManagerClass()
{
}

bool PlayerManagerClass::Initialize(ID3D11Device* device, ModelClass* player, GraphicsClass* graphics)
{
    bool result;

    m_Player = player;
    m_Graphics = graphics;

    m_Missile = new MissileClass;
    if (!m_Missile)
    {
        return false;
    }

<<<<<<< Updated upstream
    result = m_Missile->Initialize(device);
=======
    result = m_Missile->Initialize(device, this);
    if (!result)
    {
        return false;
    }

    m_StateManager = new PlayerStateManager();
    if (!m_Missile)
    {
        return false;
    }

    result = m_StateManager->Initialize(this);
    if (!result)
    {
        return false;
    }

    m_PassiveManager = new PassiveStateManager();
    if (!m_Missile)
    {
        return false;
    }

    result = m_PassiveManager->Initialize();
>>>>>>> Stashed changes
    if (!result)
    {
        return false;
    }

    return true;
}

void PlayerManagerClass::Shutdown()
{
<<<<<<< Updated upstream
    m_Missile->Shutdown();
}

void PlayerManagerClass::Frame(const DIMOUSESTATE& mouseState, const BYTE* keyboardState, 
    float frameTime, ID3D11DeviceContext* deviceContext)
{
#define GetKeyDown(key) keyboardState[key] & 0x80

    static int time = 0;
    time += 1;

    static float speed = 0.6f * 0.01f; // 0.01f = 1 / average frame
    
=======
    if (m_Missile)
    {
        m_Missile->Shutdown();
        delete m_Missile;
        m_Missile = 0;
    }

    if (m_StateManager)
    {
        m_StateManager->Shutdown();
        delete m_StateManager;
        m_StateManager = 0;
    }

    if (m_Player)
    {
        m_Player->Shutdown();
        delete m_Player;
        m_Player = 0;
    }

    if (m_Graphics)
    {
        m_Graphics->Shutdown();
        delete m_Graphics;
        m_Graphics = 0;
    }

    if (m_PassiveManager)
    {
        m_PassiveManager->Shutdown();
        delete m_PassiveManager;
        m_PassiveManager = 0;
    }

}

void PlayerManagerClass::Frame(float frameTime, ID3D11DeviceContext* deviceContext)
{
    m_StateManager->Frame();

    m_PassiveManager->Update();

    if (m_Missile->IsActivate()) m_Missile->Frame(deviceContext, frameTime);


    /*
    static float speed = 0.6f * 0.02f; // 0.01f = 1 / average frame
    
#define GetKeyDown(key) keyboardState[key] & 0x80
>>>>>>> Stashed changes
    if (GetKeyDown(DIK_A)) m_Player->Rotate(0.0f, -1.0f, 0.0f);
    if (GetKeyDown(DIK_D)) m_Player->Rotate(0.0f, 1.0f, 0.0f);
    if (GetKeyDown(DIK_W)) m_Player->Rotate(1.0f, 0.0f, 0.0f);
    if (GetKeyDown(DIK_S)) m_Player->Rotate(-1.0f, 0.0f, 0.0f);

    XMFLOAT3 move;
    XMStoreFloat3(&move, m_Player->GetForward());
    m_Player->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);
<<<<<<< Updated upstream

=======
    */

    
    /*
>>>>>>> Stashed changes
    if (mouseState.rgbButtons[0] && !m_IsFired)
    {
        m_IsFired = true;
        XMFLOAT3 playerPosition = m_Player->GetPosition();
        XMFLOAT3 upPosition;
        static float upConst = -0.5f;
        XMStoreFloat3(&upPosition, m_Player->GetUpVector());
        XMFLOAT3 forwardPosition;
        static float forwardConst = 2.0f;
        XMStoreFloat3(&forwardPosition, m_Player->GetForward());
        XMFLOAT3 missilePosition;
        missilePosition.x = playerPosition.x + upPosition.x * upConst + forwardPosition.x * forwardConst;
        missilePosition.y = playerPosition.y + upPosition.y * upConst + forwardPosition.y * forwardConst;
        missilePosition.z = playerPosition.z + upPosition.z * upConst + forwardPosition.z * forwardConst;
        m_Missile->Activate(missilePosition, m_Player->GetRotation());
        AddMissileInRender();
    }
    
    if (m_IsFired && time >= 60 * 5) {
        m_IsFired = false;
        time = 0;
        m_Missile->DeActivate();
        RemoveMissileInRender();
    }
<<<<<<< Updated upstream
    else if (m_IsFired) m_Missile->Frame(deviceContext, frameTime);
=======
    */
}

void PlayerManagerClass::HandleInput(InputManagerClass::Behavior input)
{
    m_StateManager->HandleInput(input);
>>>>>>> Stashed changes
}

void PlayerManagerClass::AddMissileInRender()
{
    m_Graphics->AddRenderObject(GraphicsClass::ShaderName::LightShader, m_Missile->GetMissile());
    m_Graphics->AddRenderObject(GraphicsClass::ShaderName::ParticleShader, m_Missile->GetParticle());
}

void PlayerManagerClass::RemoveMissileInRender()
{
    m_Graphics->RemoveRenderObject(m_Missile->GetMissile());
    m_Graphics->RemoveRenderObject(m_Missile->GetParticle());
}

<<<<<<< Updated upstream
=======
void PlayerManagerClass::DeActivateMissile()
{
    m_Missile->DeActivate();
    RemoveMissileInRender();
}

>>>>>>> Stashed changes
MissileClass* PlayerManagerClass::GetMissile()
{
    return m_Missile;
}
<<<<<<< Updated upstream
=======

ModelClass* PlayerManagerClass::GetModel()
{
    return m_Player;
}

void PlayerManagerClass::InsertPassive(Passive* passive)
{
    m_PassiveManager->InsertPassive(passive);
}

void PlayerManagerClass::RemovePassive(Passive* passive)
{
    m_PassiveManager->RemovePassive(passive);
}

bool PlayerManagerClass::FindPassive(Passive* passive)
{
    return m_PassiveManager->FindPassive(passive);
}

float PlayerManagerClass::GetSpeed()
{
    return m_Speed;
}

void PlayerManagerClass::SetSpeed(float speed)
{
    m_Speed = speed;
}

void PlayerManagerClass::ResetSpeed()
{
    m_Speed = 0.6f * 0.02f;
}
>>>>>>> Stashed changes
