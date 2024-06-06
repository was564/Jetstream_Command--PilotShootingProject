#include "BoostingCommand.h"
#include "PlayerManagerClass.h"

BoostingCommand::BoostingCommand(PlayerManagerClass* player)
    : m_Player(player)
{
    m_BoostingPassive = new Boosting(player);
}

BoostingCommand::~BoostingCommand()
{
    if(m_BoostingPassive) delete m_BoostingPassive;
}

void BoostingCommand::Execute()
{
    if(!m_Player->FindPassive(m_BoostingPassive))
        m_Player->InsertPassive(m_BoostingPassive);
}

void BoostingCommand::UnExecute()
{
    if(m_Player->FindPassive(m_BoostingPassive))
        m_Player->RemovePassive(m_BoostingPassive);
}
