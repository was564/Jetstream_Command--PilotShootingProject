#include "missileclass.h"
<<<<<<< Updated upstream
=======
#include "playermanagerclass.h"
>>>>>>> Stashed changes

MissileClass::MissileClass()
{
    m_Missile = 0;
    m_Fire = 0;
    m_Collider = 0;
<<<<<<< Updated upstream
=======
    m_RemainTimer = 0;
>>>>>>> Stashed changes
}

MissileClass::~MissileClass()
{
}

<<<<<<< Updated upstream
bool MissileClass::Initialize(ID3D11Device* device)
=======
bool MissileClass::Initialize(ID3D11Device* device, PlayerManagerClass* owner)
>>>>>>> Stashed changes
{
    bool result;

    m_Missile = new ModelClass;

    result = m_Missile->Initialize(device, L"./data/Missile.obj", L"./data/Missile.dds");
    if (!result)
    {
        return false;
    }
    m_Missile->SetScale(0.3f, 0.3f, 0.3f);

    m_Fire = new ParticleSystemClass;
    result = m_Fire->Initialize(device, L"./data/star.dds");
    if (!result)
    {
        return false;
    }

    m_Collider = new ColliderClass(2.0f, m_Missile->GetPosition());

<<<<<<< Updated upstream
=======
    m_Owner = owner;

>>>>>>> Stashed changes
    m_IsActivate = false;

    return true;
}

void MissileClass::Shutdown()
{
    if (m_Missile)
    {
        m_Missile->Shutdown();
        delete m_Missile;
        m_Missile = 0;
    }

    if (m_Fire)
    {
        m_Fire->Shutdown();
        delete m_Fire;
        m_Fire = 0;
    }

    if (m_Collider)
    {
        delete m_Collider;
        m_Collider = 0;
    }
}

void MissileClass::Activate(XMFLOAT3 position, XMFLOAT3 rotation)
{
<<<<<<< Updated upstream
    m_Missile->SetPosition(position);
    m_Missile->SetRotation(rotation);

    static float speed = -1.0f;

    XMFLOAT3 particlePosition;
    XMFLOAT3 backwardPosition;
    XMVECTOR missileForward = m_Missile->GetForward();
    XMStoreFloat3(&backwardPosition,  missileForward);

    particlePosition.x = position.x + backwardPosition.x * speed;
    particlePosition.y = position.y + backwardPosition.y * speed;
    particlePosition.z = position.z + backwardPosition.z * speed;
=======
    m_RemainTimer = 0;

    m_Missile->SetPosition(position);
    m_Missile->SetRotation(rotation);

    static float distance = -1.0f;

    XMFLOAT3 particlePosition;
    XMFLOAT3 forwardPosition;
    XMVECTOR missileForward = m_Missile->GetForward();
    XMStoreFloat3(&forwardPosition,  missileForward);

    particlePosition.x = position.x + forwardPosition.x * distance;
    particlePosition.y = position.y + forwardPosition.y * distance;
    particlePosition.z = position.z + forwardPosition.z * distance;
>>>>>>> Stashed changes
    m_Fire->SetPosition(particlePosition);

    m_IsActivate = true;
}

void MissileClass::DeActivate()
{
<<<<<<< Updated upstream
=======
    m_RemainTimer = 0;
>>>>>>> Stashed changes
    m_Collider->SetCenter(XMFLOAT3(-20.0f, -20.0f, -20.0f));
    m_IsActivate = false;
}



void MissileClass::Frame(ID3D11DeviceContext* deviceContext, float frameTime)
{
<<<<<<< Updated upstream
    static float speed = 0.2f;
=======
    static float speed = 0.4f;

    m_RemainTimer++;

    if (m_RemainTimer > 60 * 5) // 5 seconds
    {
        m_Owner->DeActivateMissile();
        return;
    }
>>>>>>> Stashed changes

    XMFLOAT3 move;
    XMVECTOR missileForward = m_Missile->GetForward();
    XMStoreFloat3(&move, missileForward);
    m_Missile->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);

<<<<<<< Updated upstream
    m_Fire->TranslatePosition(move.x, move.y, move.z);
=======
    m_Fire->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);
>>>>>>> Stashed changes

    m_Fire->Frame(frameTime, deviceContext);

    m_Collider->SetCenter(m_Missile->GetPosition());
}

ModelClass* MissileClass::GetMissile()
{
    return m_Missile;
}

ParticleSystemClass* MissileClass::GetParticle()
{
    return m_Fire;
}

ColliderClass* MissileClass::GetCollider()
{
    return m_Collider;
}

bool MissileClass::IsActivate()
{
    return m_IsActivate;
}
