#pragma once
#include "modelclass.h"
#include "particlesystemclass.h"
#include "colliderclass.h"

class MissileClass
{
public:
    MissileClass();
    ~MissileClass();

    bool Initialize(ID3D11Device*);
    void Shutdown();

    void Activate(XMFLOAT3, XMFLOAT3);
    void DeActivate();
    void Frame(ID3D11DeviceContext*, float);

    ModelClass* GetMissile();
    ParticleSystemClass* GetParticle();
    ColliderClass* GetCollider();

    bool IsActivate();
private:
    ModelClass* m_Missile;
    ParticleSystemClass* m_Fire;

    ColliderClass* m_Collider;

    bool m_IsActivate;
};

