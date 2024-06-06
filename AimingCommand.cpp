#include "AimingCommand.h"
#include "CameraManagerClass.h"

AimingCommand::AimingCommand(CameraManagerClass* camera)
    : m_Camera(camera)
{
}

AimingCommand::~AimingCommand()
{
}

void AimingCommand::Execute()
{
    m_Camera->HandleInput(InputManagerClass::Behavior::Aiming);
}
