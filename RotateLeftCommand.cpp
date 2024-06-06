#include "RotateLeftCommand.h"
#include "playermanagerclass.h"

RotateLeftCommand::RotateLeftCommand(PlayerManagerClass* player)
    : m_Player(player)
{
}

RotateLeftCommand::~RotateLeftCommand()
{
}

void RotateLeftCommand::Execute()
{
    m_Player->HandleInput(InputManagerClass::Behavior::RotateLeft);
}
