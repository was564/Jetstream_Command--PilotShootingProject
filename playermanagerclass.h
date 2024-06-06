#pragma once
#include <dinput.h>
#include "modelclass.h"
#include "missileclass.h"
<<<<<<< Updated upstream
=======
#include "PlayerStateManager.h"
#include "inputmanagerclass.h"
#include "PassiveStateManager.h"
>>>>>>> Stashed changes

class GraphicsClass;

class PlayerManagerClass
{
public:
<<<<<<< Updated upstream
=======
    

>>>>>>> Stashed changes
    PlayerManagerClass();
    ~PlayerManagerClass();

    bool Initialize(ID3D11Device*, ModelClass*, GraphicsClass*);
    void Shutdown();

<<<<<<< Updated upstream
    void Frame(const DIMOUSESTATE&, const BYTE*, float, ID3D11DeviceContext*);
=======
    void Frame(float, ID3D11DeviceContext*);
    void HandleInput(InputManagerClass::Behavior);

>>>>>>> Stashed changes

    void AddMissileInRender();
    void RemoveMissileInRender();

<<<<<<< Updated upstream
    MissileClass* GetMissile();
private:
=======
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

>>>>>>> Stashed changes
    ModelClass* m_Player;

    MissileClass* m_Missile;

    GraphicsClass* m_Graphics;

<<<<<<< Updated upstream
    bool m_IsFired;
=======
    PlayerStateManager* m_StateManager;

    PassiveStateManager* m_PassiveManager;
>>>>>>> Stashed changes
};

