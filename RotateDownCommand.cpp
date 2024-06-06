#include "RotateDownCommand.h"
#include "playermanagerclass.h"

RotateDownCommand::RotateDownCommand(PlayerManagerClass* player)
    : m_Player(player)
{
}

RotateDownCommand::~RotateDownCommand()
{
}

void RotateDownCommand::Execute()
{
    m_Player->HandleInput(InputManagerClass::Behavior::RotateDown);
}
