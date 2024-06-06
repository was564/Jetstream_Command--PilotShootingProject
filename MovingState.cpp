#include "MovingState.h"
#include "playermanagerclass.h"
#include <directxmath.h>


MovingState::MovingState(PlayerStateManager* manager)
    : PlayerStateInterface(manager), m_LeftRightDirection(0), m_UpDownDirection(0)
{
}

MovingState::~MovingState()
{
}

void MovingState::Exit()
{
    m_LeftRightDirection = 0;
    m_UpDownDirection = 0;
}

void MovingState::Update()
{
    m_Player->GetModel()->Rotate(m_UpDownDirection, m_LeftRightDirection, 0.0f);
    m_UpDownDirection = 0;
    m_LeftRightDirection = 0;

    float speed = m_Player->GetSpeed();
    XMFLOAT3 move;
    XMStoreFloat3(&move, m_Player->GetModel()->GetForward());
    m_Player->GetModel()->TranslatePosition(move.x * speed, move.y * speed, move.z * speed);
}

void MovingState::HandleInput(InputManagerClass::Behavior input)
{

    switch (input) {
        case InputManagerClass::Behavior::RotateUp:
            m_UpDownDirection += 1;
            break;

        case InputManagerClass::Behavior::RotateDown:
            m_UpDownDirection += -1;
            break;

        case InputManagerClass::Behavior::RotateLeft:  
            m_LeftRightDirection += -1;
            break;

        case InputManagerClass::Behavior::RotateRight:
            m_LeftRightDirection += 1;
            break;

        case InputManagerClass::Behavior::Fire:
            if (!(m_Player->GetMissile()->IsActivate()))
                m_StateManager->ChangeState(PlayerState::Firing);
            break;
    }
    /*
#define GetKeyDown(key) keyboardState[key] & 0x80
    if(GetKeyDown(DIK_W))
    {
        m_UpDownDirection += 1;
    }
    if (GetKeyDown(DIK_S))
    {
        m_UpDownDirection += -1;
    }
    if (GetKeyDown(DIK_A))
    {
        m_LeftRightDirection += -1;
    }
    if (GetKeyDown(DIK_D))
    {
        m_LeftRightDirection += 1;
    }
    
    if (mouseState.rgbButtons[0] && !(m_Player->GetMissile()->IsActivate())) {
        m_StateManager->ChangeState(PlayerState::Firing);
        return;
    }
    */
}


