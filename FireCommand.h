#pragma once
#include "ICommand.h"

class PlayerManagerClass;

class FireCommand : public ICommand
{
public:
    FireCommand(PlayerManagerClass*);
    ~FireCommand();

    void Execute() override;

private:
    PlayerManagerClass* m_Player;
};