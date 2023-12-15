#include "announceclass.h"

AnnouncerClass::AnnouncerClass()
{
}

AnnouncerClass::~AnnouncerClass()
{
}

void AnnouncerClass::RegisterObserver(IObserver* ob)
{
    m_observerList.insert(ob);
}

void AnnouncerClass::RemoveObserver(IObserver* ob)
{
    m_observerList.erase(ob);
}

void AnnouncerClass::Notify()
{
    for (IObserver* ob : m_observerList)
    {
        ob->UpdateByNotify();
    }
}



