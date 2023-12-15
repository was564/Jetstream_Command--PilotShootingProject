#pragma once
#include <set>
#include "observerclass.h"

class AnnouncerClass
{
public:
    AnnouncerClass();
    ~AnnouncerClass();

    void RegisterObserver(IObserver*);
    void RemoveObserver(IObserver*);

    void Notify();

private:
    std::set<IObserver*> m_observerList;
};

