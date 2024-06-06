#pragma once
#include "PlayerStateInterface.h"

class MovingState : public PlayerStateInterface
{
public:
    MovingState(PlayerStateManager*);
    ~MovingState();

    void Exit() override;
    void Update() override;
    void HandleInput(InputManagerClass::Behavior) override;

private:
    short m_LeftRightDirection; // -1 : left, 0 : stop, 1 : right

    short m_UpDownDirection; // -1 : down, 0 : stop, 1 : up
};