#include "colliderclass.h"

ColliderClass::ColliderClass(float radius, XMFLOAT3 center)
{
    m_Radius = radius;
    m_Center = center;
}

ColliderClass::~ColliderClass()
{
}

float ColliderClass::GetRadius()
{
    return m_Radius;
}

XMFLOAT3 ColliderClass::GetCenter()
{
    return m_Center;
}

void ColliderClass::SetRadius(float radius)
{
    m_Radius = radius;
}

void ColliderClass::SetCenter(const XMFLOAT3& center)
{
    m_Center = center;
}
