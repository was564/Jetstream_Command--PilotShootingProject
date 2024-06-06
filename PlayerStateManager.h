#pragma once
#include <dinput.h>
#include <map>
#include "PlayerStateInterface.h"
#include "inputmanagerclass.h"

class PlayerManagerClass;

enum class PlayerState
{
    Null = 0,
    Moving,
    Firing,
    Size
};

class PlayerStateManager
{
public:
    PlayerStateManager();
    ~PlayerStateManager();

    bool Initialize(PlayerManagerClass*);
    void Shutdown();

    void Frame();
    void HandleInput(InputManagerClass::Behavior);

    void ChangeState(PlayerState);
    PlayerState GetCurrentState();

    PlayerManagerClass* GetPlayer();

private:
    PlayerManagerClass* m_Player;

    std::map<PlayerState, PlayerStateInterface*>* m_PlayerStateMap;

    PlayerStateInterface* m_CurrentState;
};