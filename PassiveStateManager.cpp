#include "PassiveStateManager.h"

PassiveStateManager::PassiveStateManager()
{
    m_PassiveSet = 0;
}

PassiveStateManager::~PassiveStateManager()
{
}

void PassiveStateManager::Update()
{
    for (Passive* passive : *m_PassiveSet)
    {
        passive->Update();
    }
}

bool PassiveStateManager::Initialize()
{
    m_PassiveSet = new std::set<Passive*>;

    if (!m_PassiveSet) return false;

    return true;
}

void PassiveStateManager::Shutdown()
{
    for (Passive* passive : *m_PassiveSet)
    {
        delete passive;
    }

    delete m_PassiveSet;
}

void PassiveStateManager::InsertPassive(Passive* passive)
{
    passive->Enter();
    m_PassiveSet->insert(passive);
}

void PassiveStateManager::RemovePassive(Passive* passive)
{
    m_PassiveSet->erase(passive);
    passive->Exit();
}

bool PassiveStateManager::FindPassive(Passive* passive)
{
    return m_PassiveSet->end() != m_PassiveSet->find(passive);
}
