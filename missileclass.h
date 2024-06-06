#pragma once
#include "modelclass.h"
#include "particlesystemclass.h"
#include "colliderclass.h"

<<<<<<< Updated upstream
=======
class PlayerManagerClass;

>>>>>>> Stashed changes
class MissileClass
{
public:
    MissileClass();
    ~MissileClass();

<<<<<<< Updated upstream
    bool Initialize(ID3D11Device*);
=======
    bool Initialize(ID3D11Device*, PlayerManagerClass*);
>>>>>>> Stashed changes
    void Shutdown();

    void Activate(XMFLOAT3, XMFLOAT3);
    void DeActivate();
    void Frame(ID3D11DeviceContext*, float);

    ModelClass* GetMissile();
    ParticleSystemClass* GetParticle();
    ColliderClass* GetCollider();

    bool IsActivate();
<<<<<<< Updated upstream
private:
=======

private:
    PlayerManagerClass* m_Owner;

>>>>>>> Stashed changes
    ModelClass* m_Missile;
    ParticleSystemClass* m_Fire;

    ColliderClass* m_Collider;

    bool m_IsActivate;
<<<<<<< Updated upstream
=======

    int m_RemainTimer;
>>>>>>> Stashed changes
};

