#include "planemodelclass.h"
#include "graphicsclass.h"

PlaneModelClass::PlaneModelClass()
{
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);

    m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

    m_modelForward = DefaultForward;
    m_modelRight = DefaultRight;
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

PlaneModelClass::~PlaneModelClass()
{
}

void PlaneModelClass::Rotate(float rotateX, float rotateY, float rotateZ)
{
    XMFLOAT3 tempRotate = XMFLOAT3(rotateX * 0.0174532925f, rotateY * 0.0174532925f, rotateZ * 0.0174532925f);

    XMVECTOR resultVector = XMQuaternionRotationRollPitchYaw(tempRotate.x, tempRotate.y, tempRotate.z);

    XMFLOAT3 result;
    XMStoreFloat3(&result, resultVector);
    m_rotation.x += result.x;
    m_rotation.y += result.y;
    m_rotation.z += result.z;

    XMMATRIX resultMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

    m_modelRight = XMVector3TransformNormal(DefaultRight, resultMatrix);
    m_modelForward = XMVector3TransformNormal(DefaultForward, resultMatrix);
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

void PlaneModelClass::TranslatePosition(float offsetX, float offsetY, float offsetZ)
{
    m_position.x += offsetX;
    m_position.y += offsetY;
    m_position.z += offsetZ;
}

void PlaneModelClass::TranslatePosition(XMVECTOR& position)
{
    XMFLOAT3 positionFloat3;
    XMStoreFloat3(&positionFloat3, position);
    m_position.x += positionFloat3.x;
    m_position.y += positionFloat3.y;
    m_position.z += positionFloat3.z;
}

void PlaneModelClass::SetPosition(const XMFLOAT3& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.z = position.z;
}

void PlaneModelClass::SetPosition(const XMVECTOR& positionVector)
{
    XMFLOAT3 position;
    XMStoreFloat3(&position, positionVector);
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.z = position.z;
}

const XMVECTOR& PlaneModelClass::GetPosition()
{
    return XMLoadFloat3(&m_position);
}

const XMFLOAT3& PlaneModelClass::GetRotation()
{
    return m_rotation;
}

const XMVECTOR& PlaneModelClass::GetForward()
{
    return m_modelForward;
}
