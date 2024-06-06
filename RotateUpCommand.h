#pragma once
#include "ICommand.h"

class PlayerManagerClass;

class RotateUpCommand : public ICommand
{
public:
    RotateUpCommand(PlayerManagerClass*);
    ~RotateUpCommand();

    void Execute() override;

private:
    PlayerManagerClass* m_Player;
};