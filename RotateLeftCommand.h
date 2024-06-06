#pragma once
#include "ICommand.h"

class PlayerManagerClass;

class RotateLeftCommand : public ICommand
{
public:
    RotateLeftCommand(PlayerManagerClass*);
    ~RotateLeftCommand();

    void Execute() override;

private:
    PlayerManagerClass* m_Player;
};