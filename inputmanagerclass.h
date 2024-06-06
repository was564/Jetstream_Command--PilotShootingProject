#pragma once
#include <dinput.h>
#include <d3d11.h>
#include "ICommand.h"
#include "RotateDownCommand.h"
#include "RotateLeftCommand.h"
#include "RotateRightCommand.h"
#include "RotateUpCommand.h"
#include "FireCommand.h"
#include "AimingCommand.h"
#include "BoostingCommand.h"
#include "StoppingCommand.h"
#include "BoosterCommand.h"

class PlayerManagerClass;
class CameraManagerClass;

class InputManagerClass 
{
public:
    enum class Behavior
    {
        None = 0,
        RotateUp,
        RotateDown,
        RotateLeft,
        RotateRight,
        Fire,
        Aiming,

        Boosting,
        Stopping,
        Booster,
        Size
    };

    InputManagerClass();
    ~InputManagerClass();

    bool Initialize(PlayerManagerClass*, CameraManagerClass*);
    void Shutdown();

    bool Frame(const DIMOUSESTATE&, const BYTE*);

private:

    ICommand* m_ButtonW;
    ICommand* m_ButtonS;
    ICommand* m_ButtonA;
    ICommand* m_ButtonD;

    ICommand* m_ButtonLeftClick;
    ICommand* m_ButtonRightClick;

    ICommand* m_ButtonShift;
    ICommand* m_ButtonCtrl;
    ICommand* m_ButtonSpace;
};