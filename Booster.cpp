#include "Stopping.h"
#include "PlayerManagerClass.h"
#include "Booster.h"

Booster::Booster(PlayerManagerClass* player)
    : m_Player(player), m_BoosterSpeed(0.5f), m_InitSpeed(0.0f)
{
}

Booster::~Booster()
{
}

void Booster::Enter()
{
    m_InitSpeed = m_Player->GetSpeed();
}

void Booster::Exit()
{
    m_Player->SetSpeed(m_InitSpeed);
}

void Booster::Update()
{
    m_Player->SetSpeed(m_InitSpeed + m_BoosterSpeed);
}
