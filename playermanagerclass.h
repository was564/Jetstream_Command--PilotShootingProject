#pragma once
#include <dinput.h>
#include "modelclass.h"
#include "missileclass.h"
#include "PlayerStateManager.h"
#include "inputmanagerclass.h"
#include "PassiveStateManager.h"

class GraphicsClass;

class PlayerManagerClass
{
public:
    

    PlayerManagerClass();
    ~PlayerManagerClass();

    bool Initialize(ID3D11Device*, ModelClass*, GraphicsClass*);
    void Shutdown();

    void Frame(float, ID3D11DeviceContext*);
    void HandleInput(InputManagerClass::Behavior);


    void AddMissileInRender();
    void RemoveMissileInRender();

    void DeActivateMissile();

    MissileClass* GetMissile();
    ModelClass* GetModel();

    void InsertPassive(Passive*);
    void RemovePassive(Passive*);

    bool FindPassive(Passive*);

    float GetSpeed();

    void SetSpeed(float);
    void ResetSpeed();

private:
    float m_Speed = 0.6f * 0.02f; // 0.01f = 1 / average frame

    ModelClass* m_Player;

    MissileClass* m_Missile;

    GraphicsClass* m_Graphics;

    PlayerStateManager* m_StateManager;

    PassiveStateManager* m_PassiveManager;
};

