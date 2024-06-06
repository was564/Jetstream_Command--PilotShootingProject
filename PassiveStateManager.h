#pragma once
#include <set>
#include "Passive.h"


class PassiveStateManager
{
    public:
    PassiveStateManager();
    ~PassiveStateManager();

    void Update();
    
    bool Initialize();
    void Shutdown();

    void InsertPassive(Passive*);
    void RemovePassive(Passive*);

    bool FindPassive(Passive*);

private:
    std::set<Passive*>* m_PassiveSet;
};

