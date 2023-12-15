#include "playermanagerclass.h"
#include "graphicsclass.h"

PlayerManagerClass::PlayerManagerClass()
{
    m_Player = 0;
    m_Missile = 0;
    m_IsFired = false;
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

    result = m_Missile->Initialize(device);
    if (!result)
    {
        return false;
    }

    return true;
}

void PlayerManagerClass::Shutdown()
{
    m_Missile->Shutdown();
}

void PlayerManagerClass::Frame(const DIMOUSESTATE& mouseState, const BYTE* keyboardState, 
    float frameTime, ID3D11DeviceContext* deviceContext)
{
#define GetKeyDown(key) keyboardState[key] & 0x80

    static int time = 0;
    time += 1;

    static float speed = 0.6f * 0.01f; // 0.01f = 1 / average frame
    
    if (GetKeyDown(DIK_A)) m_Player->Rotate(0.0f, -1.0f, 0.0f);
    if (GetKeyDown(DIK_D)) m_Player->Rotate(0.0f, 1.0f, 0.0f);
    if (GetKeyDown(DIK_W)) m_Player->Rotate(1.0f, 0.0f, 0.0f);
    if (GetKeyDown(DIK_S)) m_Player->Rotate(-1.0f, 0.0f, 0.0f);

    XMFLOAT3 move;
    XMStoreFloat3(&move, m_Player->GetForward());
    m_Player->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);

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
    else if (m_IsFired) m_Missile->Frame(deviceContext, frameTime);
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

MissileClass* PlayerManagerClass::GetMissile()
{
    return m_Missile;
}
