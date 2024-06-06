#include "BoosterCommand.h"
#include "PlayerManagerClass.h"

BoosterCommand::BoosterCommand(PlayerManagerClass* player)
    : m_Player(player)
{
    m_BoosterPassive = new Booster(player);
}

BoosterCommand::~BoosterCommand()
{
    if (m_BoosterPassive) delete m_BoosterPassive;
}

void BoosterCommand::Execute()
{
    if (!m_Player->FindPassive(m_BoosterPassive))
        m_Player->InsertPassive(m_BoosterPassive);
}

void BoosterCommand::UnExecute()
{
    if (m_Player->FindPassive(m_BoosterPassive))
        m_Player->RemovePassive(m_BoosterPassive);
}
