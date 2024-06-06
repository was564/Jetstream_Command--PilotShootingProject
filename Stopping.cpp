#include "Stopping.h"
#include "PlayerManagerClass.h"

Stopping::Stopping(PlayerManagerClass* player)
    : m_Player(player), m_MinSpeed(0.03f)
{
}

Stopping::~Stopping()
{
}

void Stopping::Update()
{
    if (m_Player->GetSpeed() < m_MinSpeed) return;
    m_Player->SetSpeed(m_Player->GetSpeed() - 0.2f * 0.006f);
}
