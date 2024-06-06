#pragma once
#include "ICommand.H"
#include "Stopping.h"

class PlayerManagerClass;

class StoppingCommand : public ICommand
{
public:
    StoppingCommand(PlayerManagerClass*);
    ~StoppingCommand();

    void Execute() override;
    void UnExecute() override;

private:
    Passive* m_StoppingPassive;
    PlayerManagerClass* m_Player;
};

