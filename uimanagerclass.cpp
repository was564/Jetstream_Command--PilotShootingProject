#include "uimanagerclass.h"

UIManagerClass::UIManagerClass()
{
    
}

UIManagerClass::~UIManagerClass()
{
}

bool UIManagerClass::Initialize(CameraManagerClass* cameraManager)
{
    m_Mode = cameraManager;
    
    cameraManager->RegisterObserver(this);
    return true;
}

void UIManagerClass::Frame()
{
    
}

void UIManagerClass::UpdateByNotify()
{
    CameraManagerClass::CameraMode currentMode = m_Mode->GetMode();

    if (currentMode == CameraManagerClass::CameraMode::ThirdPerspectMode)
    {

    }
    else if (currentMode == CameraManagerClass::CameraMode::AimingMode)
    {

    }
}
