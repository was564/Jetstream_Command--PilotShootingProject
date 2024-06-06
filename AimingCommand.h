#pragma once
#include "ICommand.h"

class CameraManagerClass;

class AimingCommand : public ICommand
{
public:
    AimingCommand(CameraManagerClass*);
    ~AimingCommand();

    void Execute() override;

private:
    CameraManagerClass* m_Camera;
};