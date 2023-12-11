#pragma once
#include "modelclass.h"

class PlaneModelClass : public ModelClass
{
private:


public:
    PlaneModelClass();
    ~PlaneModelClass();

    void Rotate(float, float, float);

    void TranslatePosition(float, float, float);
    void TranslatePosition(XMVECTOR&);
    void SetPosition(const XMFLOAT3& position);
    void SetPosition(const XMVECTOR& positionVector);
    const XMVECTOR& GetPosition();
    const XMFLOAT3& GetRotation();
    const XMVECTOR& GetForward();
private:
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;

    XMVECTOR m_modelForward;
    XMVECTOR m_modelRight;
    XMVECTOR m_modelUp;
};