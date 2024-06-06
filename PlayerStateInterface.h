#pragma once
#include <dinput.h>
#include "InputManagerClass.h"

class PlayerStateManager;
class PlayerManagerClass;

class PlayerStateInterface
{
public:
    PlayerStateInterface(PlayerStateManager*);
    ~PlayerStateInterface();

    virtual void Enter() {}
    virtual void Exit() {}
    virtual void Update() = 0;
    virtual void HandleInput(InputManagerClass::Behavior) {}

protected:
    PlayerStateManager* m_StateManager;
    
    PlayerManagerClass* m_Player;
};