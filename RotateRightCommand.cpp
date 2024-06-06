#include "RotateRightCommand.h"
#include "playermanagerclass.h"

RotateRightCommand::RotateRightCommand(PlayerManagerClass* player)
    : m_Player(player)
{
}

RotateRightCommand::~RotateRightCommand()
{
}

void RotateRightCommand::Execute()
{
    m_Player->HandleInput(InputManagerClass::Behavior::RotateRight);
}
