#include "PlayerStateManager.h"
#include "PlayerStateInterface.h"
#include "playermanagerclass.h"
#include "MovingState.h"
#include "FiringState.h"

PlayerStateManager::PlayerStateManager()
{
}

PlayerStateManager::~PlayerStateManager()
{
}

bool PlayerStateManager::Initialize(PlayerManagerClass* player)
{
    m_Player = player;

    m_PlayerStateMap = new map<PlayerState, PlayerStateInterface*>;
    m_PlayerStateMap->insert(pair<PlayerState, PlayerStateInterface*>(PlayerState::Moving, new MovingState(this)));
    m_PlayerStateMap->insert(pair<PlayerState, PlayerStateInterface*>(PlayerState::Firing, new FiringState(this)));

    m_CurrentState = (*m_PlayerStateMap)[PlayerState::Moving];

    return true;
}

void PlayerStateManager::Shutdown()
{
    for (pair<PlayerState, PlayerStateInterface*> state : *m_PlayerStateMap)
    {
        delete state.second;
    }

    delete m_PlayerStateMap;
}

void PlayerStateManager::Frame()
{
    m_CurrentState->Update();
}

void PlayerStateManager::HandleInput(InputManagerClass::Behavior input)
{
    m_CurrentState->HandleInput(input);
}

void PlayerStateManager::ChangeState(PlayerState nextState)
{
    m_CurrentState->Exit();

    m_CurrentState = (*m_PlayerStateMap)[nextState];

    m_CurrentState->Enter();
}

PlayerState PlayerStateManager::GetCurrentState()
{
    return PlayerState();
}

PlayerManagerClass* PlayerStateManager::GetPlayer()
{
    return m_Player;
}


