#include "enemymanagerclass.h"
#include "graphicsclass.h"
#include "collisionmanagerclass.h"
#include <queue>

EnemyManagerClass::EnemyManagerClass()
{
}

EnemyManagerClass::~EnemyManagerClass()
{
}

bool EnemyManagerClass::Initialize(ID3D11Device* device, GraphicsClass* graphics, int enemyCount)
{
    srand((unsigned int)time(NULL));
    bool result;

    m_Graphics = graphics;


    for (int i = 0; i < enemyCount; i++)
    {
        EnemyPlaneClass* enemyModel = new EnemyPlaneClass;
        result = enemyModel->Initialize(device);
        if (!result)
        {
            return false;
        }
        m_AvailableEnemyQueue.push(enemyModel);
        SpawnEnemy(((rand()%60) - 30.0f), (rand()%20), ((rand() % 60) - 30.0f));
    }

    return true;
}

void EnemyManagerClass::Shutdown()
{
    for (int i = 0; i < m_AvailableEnemyQueue.size(); i++)
    {
        EnemyPlaneClass* model = m_AvailableEnemyQueue.front();
        m_AvailableEnemyQueue.pop();
        if (model) 
        {
            model->Shutdown();
            delete model;
            model = 0;
        }
    }

    for (EnemyPlaneClass* model : m_UsedEnemySet)
    {
        if (model)
        {
            model->Shutdown();
            delete model;
            model = 0;
        }
    }
}

void EnemyManagerClass::Frame(MissileClass* missile)
{
    bool isChangedMode = false;
    static int time = 0;
    time += 1;
    queue<EnemyPlaneClass*> enemySetForRemove;
    queue<EnemyPlaneClass*> enemySetForChangingShader;
    for (EnemyPlaneClass* model : m_UsedEnemySet)
    {
        model->Frame();

        if (!model->IsActivate()) enemySetForRemove.push(model);

        if (missile->IsActivate() && model->IsActivate() &&
            CollisionManagerClass::CheckCollisionSphereColliders(missile->GetCollider(), model->GetCollider()))
        {
            model->ChangeMode(EnemyPlaneClass::EnemyMode::Die);
            enemySetForChangingShader.push(model);
            continue;
        }

        if (model->GetMode() != EnemyPlaneClass::EnemyMode::Die && time >= 60 * 10)
        {
            isChangedMode = true;
            model->ChangeModeRandom();
        }
    }
    if (isChangedMode) time = 0;

    while (enemySetForRemove.size() > 0) {
        DestroyEnemy(enemySetForRemove.front());
        enemySetForRemove.pop();
    }

    while (enemySetForChangingShader.size() > 0) {
        EnemyPlaneClass* enemy = enemySetForChangingShader.front();
        enemySetForChangingShader.pop();

        m_Graphics->RemoveRenderObject(enemy->GetModel());
        m_Graphics->AddRenderObject(GraphicsClass::ShaderName::FireShader, enemy->GetModel());
    }

    while (m_AvailableEnemyQueue.size() > 0) {
        SpawnEnemy(((rand() % 60) - 30.0f), (rand() % 20), ((rand() % 60) - 30.0f));
    }
}

void EnemyManagerClass::SpawnEnemy(float positionX, float positionY, float positionZ)
{
    if (m_AvailableEnemyQueue.size() <= 0) return;
    
    EnemyPlaneClass* object = m_AvailableEnemyQueue.front();
    m_AvailableEnemyQueue.pop();
    object->GetModel()->SetPosition(positionX, positionY, positionZ);
    XMFLOAT3 playerRotation = object->GetModel()->GetRotation();
    playerRotation.x = 0;
    object->GetModel()->SetRotation(playerRotation);
    object->ChangeModeRandom();
    m_UsedEnemySet.insert(object);
    object->SetActivate(true);

    m_Graphics->AddRenderObject(GraphicsClass::ShaderName::LightShader, object->GetModel());
}

void EnemyManagerClass::DestroyEnemy(EnemyPlaneClass* enemy)
{
    enemy->SetActivate(false);
    m_Graphics->RemoveRenderObject(enemy->GetModel());
    m_UsedEnemySet.erase(enemy);
    m_AvailableEnemyQueue.push(enemy);
}
