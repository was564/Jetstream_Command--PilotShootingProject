#pragma once
#include "cameramanagerclass.h"
#include "observerclass.h"

class UIManagerClass : public IObserver
{
public:
    UIManagerClass();
    ~UIManagerClass();

    bool Initialize(CameraManagerClass*);
    void Frame();
    void UpdateByNotify();
private:
    CameraManagerClass* m_Mode;
};

