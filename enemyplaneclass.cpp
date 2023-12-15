#include "enemyplaneclass.h"

EnemyPlaneClass::EnemyPlaneClass()
{
    m_Enemy = 0;
    m_Collider = 0;
}

EnemyPlaneClass::~EnemyPlaneClass()
{
}

bool EnemyPlaneClass::Initialize(ID3D11Device* device)
{
    bool result;

    m_Enemy = new ModelClass;
    result = m_Enemy->Initialize(device, L"./data/EnemyAirCraft.obj", L"./data/EnemyAirCraft.dds");
    if (!result)
    {
        return false;
    }

    m_Collider = new ColliderClass(5.0f, m_Enemy->GetPosition());

    m_Mode = EnemyMode::Straight;

    m_time = 0;
    m_IsActivate = false;

    return true;
}

void EnemyPlaneClass::Shutdown()
{
    if (m_Enemy)
    {
        m_Enemy->Shutdown();
        delete m_Enemy;
        m_Enemy = 0;
    }

    if (m_Collider)
    {
        delete m_Collider;
        m_Collider = 0;
    }
}

void EnemyPlaneClass::Frame()
{
    static float speed = -0.06f;

    

    switch (m_Mode)
    {
    case EnemyPlaneClass::Left:
        m_Enemy->Rotate(0.0f, -1.0f, 0.0f);
        break;
    case EnemyPlaneClass::Right:
        m_Enemy->Rotate(0.0f, 1.0f, 0.0f);
        break;
    case EnemyPlaneClass::Straight:
        break;
    case EnemyPlaneClass::Die:
        m_Enemy->Rotate(-1.0f, 0.0f, 0.0f);
        break;
    default:
        break;
    }

    XMFLOAT3 move;
    XMStoreFloat3(&move, m_Enemy->GetForward());
    m_Enemy->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);

    m_Collider->SetCenter(m_Enemy->GetPosition());

    
    if (m_Mode == EnemyMode::Die) {
        m_time += 1;
        if (m_time >= 60 * 4) {
            m_IsActivate = false;
            m_time = 0;
        }
            return;
    }
}

ModelClass* EnemyPlaneClass::GetModel()
{
    return m_Enemy;
}

ColliderClass* EnemyPlaneClass::GetCollider()
{
    return m_Collider;
}

void EnemyPlaneClass::ChangeModeRandom()
{
    m_Mode = (EnemyMode)(rand() % EnemyMode::Die);
}

void EnemyPlaneClass::ChangeMode(EnemyMode mode)
{
    m_Mode = mode;
}

EnemyPlaneClass::EnemyMode EnemyPlaneClass::GetMode()
{
    return m_Mode;
}

bool EnemyPlaneClass::IsActivate()
{
    return m_IsActivate;
}

void EnemyPlaneClass::SetActivate(bool isActivate)
{
    m_IsActivate = isActivate;
}
