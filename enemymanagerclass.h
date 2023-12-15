#pragma once
#include "modelclass.h"
#include "enemyplaneclass.h"
#include "missileclass.h"
#include <set>
#include <queue>

class GraphicsClass;

class EnemyManagerClass
{
public:
    EnemyManagerClass();
    ~EnemyManagerClass();
    
    bool Initialize(ID3D11Device*, GraphicsClass*, int);
    void Shutdown();

    void Frame(MissileClass*);

    void SpawnEnemy(float, float, float);
    void DestroyEnemy(EnemyPlaneClass*);

private:
    std::queue<EnemyPlaneClass*> m_AvailableEnemyQueue;
    std::set<EnemyPlaneClass*> m_UsedEnemySet;

    GraphicsClass* m_Graphics;
};