#include "Boosting.h"
#include "PlayerManagerClass.h"

Boosting::Boosting(PlayerManagerClass* player)
    : m_Player(player), m_MaxSpeed(1.5f)
{
}

Boosting::~Boosting()
{
}

void Boosting::Update()
{
    if (m_Player->GetSpeed() > m_MaxSpeed) return;
    m_Player->SetSpeed(m_Player->GetSpeed() + 0.2f * 0.006f);
}
