#include "inputmanagerclass.h"


InputManagerClass::InputManagerClass()
{
    m_ButtonW = 0;
    m_ButtonS = 0;
    m_ButtonA = 0;
    m_ButtonD = 0;
    m_ButtonLeftClick = 0;
    m_ButtonRightClick = 0;

    m_ButtonShift = 0;
    m_ButtonCtrl = 0;
    m_ButtonSpace = 0;
}

InputManagerClass::~InputManagerClass()
{
}

bool InputManagerClass::Initialize(PlayerManagerClass* player, CameraManagerClass* camera)
{
    m_ButtonW = new RotateUpCommand(player);
    if (!m_ButtonW) return false;

    m_ButtonS = new RotateDownCommand(player);
    if (!m_ButtonS) return false;

    m_ButtonA = new RotateLeftCommand(player);
    if (!m_ButtonA) return false;

    m_ButtonD = new RotateRightCommand(player);
    if (!m_ButtonD) return false;


    m_ButtonLeftClick = new FireCommand(player);
    if (!m_ButtonLeftClick) return false;

    m_ButtonRightClick = new AimingCommand(camera);
    if (!m_ButtonRightClick) return false;


    m_ButtonShift = new BoostingCommand(player);
    if (!m_ButtonShift) return false;

    m_ButtonSpace = new StoppingCommand(player);
    if (!m_ButtonSpace) return false;

    m_ButtonCtrl = new BoosterCommand(player);
    if (!m_ButtonCtrl) return false;

    return true;
}

void InputManagerClass::Shutdown()
{
    if (m_ButtonA) delete m_ButtonA;
    if (m_ButtonD) delete m_ButtonD;
    if (m_ButtonS) delete m_ButtonS;
    if (m_ButtonW) delete m_ButtonW;

    if (m_ButtonLeftClick) delete m_ButtonLeftClick;
    if (m_ButtonRightClick) delete m_ButtonRightClick;

    if (m_ButtonShift) delete m_ButtonShift;
    if (m_ButtonCtrl) delete m_ButtonCtrl;
    if (m_ButtonSpace) delete m_ButtonSpace;
}

bool InputManagerClass::Frame(const DIMOUSESTATE& mouseState, const BYTE* keyboardState)
{
#define GetKeyDown(key) keyboardState[key] & 0x80

    if(GetKeyDown(DIK_W)) m_ButtonW->Execute();
    else m_ButtonW->UnExecute();
    if(GetKeyDown(DIK_S)) m_ButtonS->Execute();
    else m_ButtonS->UnExecute();
    if(GetKeyDown(DIK_A)) m_ButtonA->Execute();
    else m_ButtonA->UnExecute();
    if(GetKeyDown(DIK_D)) m_ButtonD->Execute();
    else m_ButtonD->UnExecute();

    static bool isLeftClicked = false;
    static bool isRightClicked = false;


    if (mouseState.rgbButtons[0] && !isLeftClicked)
    {
        m_ButtonLeftClick->Execute();
        isLeftClicked = true;
    }
    else if(!mouseState.rgbButtons[0]) isLeftClicked = false;

    if(!isLeftClicked) m_ButtonLeftClick->UnExecute();

    if (mouseState.rgbButtons[1] && !isRightClicked)
    {
        m_ButtonRightClick->Execute();
        isRightClicked = true;
    }
    else if(!mouseState.rgbButtons[1]) isRightClicked = false;

    if(!isRightClicked) m_ButtonRightClick->UnExecute();


    if(GetKeyDown(DIK_LSHIFT)) m_ButtonShift->Execute();
    else m_ButtonShift->UnExecute();

    if(GetKeyDown(DIK_SPACE)) m_ButtonSpace->Execute();
    else m_ButtonSpace->UnExecute();

    if (GetKeyDown(DIK_LCONTROL)) m_ButtonCtrl->Execute();
    else m_ButtonCtrl->UnExecute();

    return true;
}
