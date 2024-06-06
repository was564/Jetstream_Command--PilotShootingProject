#pragma once
#include "ICommand.h"

class PlayerManagerClass;

class RotateRightCommand : public ICommand
{
public:
    RotateRightCommand(PlayerManagerClass*);
    ~RotateRightCommand();

    void Execute() override;

private:
    PlayerManagerClass* m_Player;
};