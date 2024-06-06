#pragma once
#include "ICommand.H"
#include "Booster.h"

class PlayerManagerClass;

class BoosterCommand : public ICommand
{
public:
    BoosterCommand(PlayerManagerClass*);
    ~BoosterCommand();

    void Execute() override;
    void UnExecute() override;

private:
    Passive* m_BoosterPassive;
    PlayerManagerClass* m_Player;
};

