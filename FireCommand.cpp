#include "FireCommand.h"
#include "playermanagerclass.h"

FireCommand::FireCommand(PlayerManagerClass* player)
    : m_Player(player)
{
}

FireCommand::~FireCommand()
{
}

void FireCommand::Execute()
{
    m_Player->HandleInput(InputManagerClass::Behavior::Fire);
}
