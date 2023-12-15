#pragma once
#include "modelclass.h"
#include "colliderclass.h"

class EnemyPlaneClass
{
public:
    enum EnemyMode
    {
        Left = 0,
        Right,
        Straight,
        Die,
        Size
    };

public:
    EnemyPlaneClass();
    ~EnemyPlaneClass();

    bool Initialize(ID3D11Device*);
    void Shutdown();

    void Frame();

    ModelClass* GetModel();
    ColliderClass* GetCollider();

    void ChangeModeRandom();
    void ChangeMode(EnemyMode);
    EnemyMode GetMode();

    bool IsActivate();
    void SetActivate(bool);
private:
    ModelClass* m_Enemy;
    ColliderClass* m_Collider;

    EnemyMode m_Mode;

    int m_time;
    bool m_IsActivate;
};

