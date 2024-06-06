#include "PlayerStateInterface.h"
#include "playermanagerclass.h"
#include "PlayerStateManager.h"

PlayerStateInterface::PlayerStateInterface(PlayerStateManager* manager)
    : m_StateManager(manager), m_Player(manager->GetPlayer())
{
}

PlayerStateInterface::~PlayerStateInterface()
{
}
