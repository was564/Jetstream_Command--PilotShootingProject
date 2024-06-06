#pragma once

class ICommand
{
public:

    ICommand();
    ~ICommand();

    virtual void Execute() = 0;
    virtual void UnExecute() {};
};