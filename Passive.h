#pragma once

class PlayerManagerClass;

class Passive
{
public:
    Passive();
    ~Passive();

    virtual void Enter() {}
    virtual void Update() = 0;
    virtual void Exit() {}
        
};

