#pragma once
#include "Passive.h"

class PlayerManagerClass;

class Booster : public Passive
{
public:
    Booster(PlayerManagerClass*);
    ~Booster();

    void Enter() override;
    void Update() override;
    void Exit() override;

private:
    PlayerManagerClass* m_Player;

    float m_BoosterSpeed;

    float m_InitSpeed;
};

