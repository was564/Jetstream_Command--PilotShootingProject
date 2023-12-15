#pragma once
#include <dinput.h>
#include "modelclass.h"
#include "missileclass.h"

class GraphicsClass;

class PlayerManagerClass
{
public:
    PlayerManagerClass();
    ~PlayerManagerClass();

    bool Initialize(ID3D11Device*, ModelClass*, GraphicsClass*);
    void Shutdown();

    void Frame(const DIMOUSESTATE&, const BYTE*, float, ID3D11DeviceContext*);

    void AddMissileInRender();
    void RemoveMissileInRender();

    MissileClass* GetMissile();
private:
    ModelClass* m_Player;

    MissileClass* m_Missile;

    GraphicsClass* m_Graphics;

    bool m_IsFired;
};

