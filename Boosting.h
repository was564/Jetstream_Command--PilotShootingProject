#pragma once
#include "Passive.h"

class PlayerManagerClass;

class Boosting : public Passive
{
    public:
    Boosting(PlayerManagerClass*);
    ~Boosting();

    void Update() override;

private:
    PlayerManagerClass* m_Player;

    float m_MaxSpeed;
};

