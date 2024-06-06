#pragma once
#include "PlayerStateInterface.h"

class FiringState : public PlayerStateInterface
{
public:
    FiringState(PlayerStateManager*);
    ~FiringState();

    void Enter() override;
    void Exit() override;
    void Update() override;
    
private:
    int m_Timer;
};