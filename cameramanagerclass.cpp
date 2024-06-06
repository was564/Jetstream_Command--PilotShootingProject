#include "cameramanagerclass.h"

CameraManagerClass::CameraManagerClass()
{
    m_Mode = CameraMode::ThirdPerspectMode;
}

CameraManagerClass::~CameraManagerClass()
{
}

bool CameraManagerClass::Initialize(ModelClass* player, XMFLOAT3 defaultPosition)
{
    m_Player = player;

    for (int mode = 0; mode < CameraMode::Size; mode++) {
        CameraClass* camera = new CameraClass;
        // Set the initial position of the camera.
        camera->SetPosition(defaultPosition);
        camera->SetRotation(0.0f, 0.0f, 0.0f);
        camera->Render();
        m_CameraList.push_back(camera);
    }

    return true;
}

CameraClass* CameraManagerClass::GetCameraInstance()
{
    return m_CameraList[m_Mode];
}

CameraManagerClass::CameraMode CameraManagerClass::GetMode()
{
    return m_Mode;
}

void CameraManagerClass::ChangeMode(CameraMode mode)
{
    if (0 <= mode && mode < CameraMode::Size)
        if (mode != m_Mode) AnnouncerClass::Notify();
        m_Mode = mode;
}

// how to use: mouseMovingValue (lx, ly), keyboard[ key ]
<<<<<<< Updated upstream
void CameraManagerClass::Frame(const DIMOUSESTATE& mouseState, const BYTE* keyboardState)
{
=======
void CameraManagerClass::Frame(const DIMOUSESTATE& mouseState)
{
    /*
>>>>>>> Stashed changes
    // keyboard Mouse Input Process
#define GetKeyDown(key) keyboardState[key] & 0x80

    if (mouseState.rgbButtons[1]) m_Mode = CameraMode::AimingMode;
    else m_Mode = CameraMode::ThirdPerspectMode;
<<<<<<< Updated upstream
=======
    */
>>>>>>> Stashed changes

    static float mouseSensibility = 0.1f;
    CameraClass* currentCamera = m_CameraList[m_Mode];

    if (m_Mode == CameraMode::ThirdPerspectMode)
    {
        currentCamera->SetPosition(m_Player->GetPosition());
        currentCamera->Rotate(
            mouseState.lY * mouseSensibility,
            mouseState.lX * mouseSensibility,
            0.0f);
    }
    else if (m_Mode == CameraMode::AimingMode) {

        XMFLOAT3 cameraRotation = m_Player->GetRotation();
        currentCamera->SetRotation(cameraRotation);
        currentCamera->Rotate(25.0f, 0.0f, 0.0f);

        XMFLOAT3 playerPosition = m_Player->GetPosition();
        XMFLOAT3 playerUp;
        XMStoreFloat3(&playerUp, m_Player->GetUpVector());

        XMFLOAT3 cameraActualPosition = currentCamera->GetActualPosition();
        XMFLOAT3 cameraTargetPosition = currentCamera->GetPosition();
        XMFLOAT3 cameraPositionDiff;
        cameraPositionDiff.x = cameraTargetPosition.x - cameraActualPosition.x;
        cameraPositionDiff.y = cameraTargetPosition.y - cameraActualPosition.y;
        cameraPositionDiff.z = cameraTargetPosition.z - cameraActualPosition.z;

        XMFLOAT3 cameraPosition;
        cameraPosition.x = playerPosition.x + cameraPositionDiff.x + (playerUp.x * -0.1f);
        cameraPosition.y = playerPosition.y + cameraPositionDiff.y + (playerUp.y * -0.1f);
        cameraPosition.z = playerPosition.z + cameraPositionDiff.z + (playerUp.z * -0.1f);

        currentCamera->SetPosition(cameraPosition);
    }
}
<<<<<<< Updated upstream
=======

void CameraManagerClass::HandleInput(InputManagerClass::Behavior input)
{
    switch (input) {
        case InputManagerClass::Behavior::Aiming:
            if(m_Mode == AimingMode) m_Mode = CameraMode::ThirdPerspectMode;
            else if(m_Mode == ThirdPerspectMode) m_Mode = CameraMode::AimingMode;
            break;
    }
}
>>>>>>> Stashed changes
