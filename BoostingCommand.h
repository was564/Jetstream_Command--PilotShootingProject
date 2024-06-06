#pragma once
#include "ICommand.H"
#include "Boosting.h"

class PlayerManagerClass;

class BoostingCommand : public ICommand
{
    public:
    BoostingCommand(PlayerManagerClass*);
    ~BoostingCommand();

    void Execute() override;
    void UnExecute() override;

private:
    Passive* m_BoostingPassive;
    PlayerManagerClass* m_Player;
};

