#pragma once
#include "Passive.h"

class PlayerManagerClass;

class Stopping : public Passive
{
public:
    Stopping(PlayerManagerClass*);
    ~Stopping();

    void Update() override;

private:
    PlayerManagerClass* m_Player;

    float m_MinSpeed;
};

