#include "FiringState.h"
#include "playermanagerclass.h"
#include <directxmath.h>

FiringState::FiringState(PlayerStateManager* manager)
    : PlayerStateInterface(manager), m_Timer(0)
{
}

FiringState::~FiringState()
{
}

void FiringState::Enter()
{
    m_Timer = 0;
}

void FiringState::Exit()
{
    m_Timer = 0;
    
}

void FiringState::Update()
{
    float speed = m_Player->GetSpeed();
    XMFLOAT3 move;
    XMStoreFloat3(&move, m_Player->GetModel()->GetForward());
    m_Player->GetModel()->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);

    m_Timer++;
    if (m_Timer > 60 * 0.5f) // 0.5 second
    {
        XMFLOAT3 playerPosition = m_Player->GetModel()->GetPosition();
        XMFLOAT3 upPosition;
        static float upConst = -0.5f;
        XMStoreFloat3(&upPosition, m_Player->GetModel()->GetUpVector());
        XMFLOAT3 forwardPosition;
        static float forwardConst = 2.0f;
        XMStoreFloat3(&forwardPosition, m_Player->GetModel()->GetForward());
        XMFLOAT3 missilePosition;
        missilePosition.x = playerPosition.x + upPosition.x * upConst + forwardPosition.x * forwardConst;
        missilePosition.y = playerPosition.y + upPosition.y * upConst + forwardPosition.y * forwardConst;
        missilePosition.z = playerPosition.z + upPosition.z * upConst + forwardPosition.z * forwardConst;
        m_Player->GetMissile()->Activate(missilePosition, m_Player->GetModel()->GetRotation());
        m_Player->AddMissileInRender();

        m_StateManager->ChangeState(PlayerState::Moving);
    }
}

