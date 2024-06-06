#include "StoppingCommand.h"
#include "PlayerManagerClass.h"

StoppingCommand::StoppingCommand(PlayerManagerClass* player)
    : m_Player(player)
{
    m_StoppingPassive = new Stopping(player);
}

StoppingCommand::~StoppingCommand()
{
    if (m_StoppingPassive) delete m_StoppingPassive;
}

void StoppingCommand::Execute()
{
    if (!m_Player->FindPassive(m_StoppingPassive))
        m_Player->InsertPassive(m_StoppingPassive);
}

void StoppingCommand::UnExecute()
{
    if (m_Player->FindPassive(m_StoppingPassive))
        m_Player->RemovePassive(m_StoppingPassive);
}
