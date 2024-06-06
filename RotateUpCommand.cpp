#include "RotateUpCommand.h"
#include "playermanagerclass.h"

RotateUpCommand::RotateUpCommand(PlayerManagerClass* player)
    : m_Player(player)
{
}

RotateUpCommand::~RotateUpCommand()
{
}

void RotateUpCommand::Execute()
{
    m_Player->HandleInput(InputManagerClass::Behavior::RotateUp);
}
