#pragma once
#include "ICommand.h"

class PlayerManagerClass;

class RotateDownCommand : public ICommand
{
public:
    RotateDownCommand(PlayerManagerClass*);
    ~RotateDownCommand();

    void Execute() override;

private:
    PlayerManagerClass* m_Player;
};