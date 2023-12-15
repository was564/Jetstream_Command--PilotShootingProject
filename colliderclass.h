#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class ColliderClass
{
public:
    ColliderClass(float, XMFLOAT3);
    ~ColliderClass();

    float GetRadius();
    XMFLOAT3 GetCenter();

    void SetRadius(float);
    void SetCenter(const XMFLOAT3&);
private:
    float m_Radius;
    XMFLOAT3 m_Center;
};

