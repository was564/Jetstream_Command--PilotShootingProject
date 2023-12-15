#include "objectclass.h"
#include "graphicsclass.h"

ObjectClass::ObjectClass()
{
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);

    m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

    m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

    m_modelForward = DefaultForward;
    m_modelRight = DefaultRight;
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

ObjectClass::~ObjectClass()
{
}

void ObjectClass::Rotate(float rotateX, float rotateY, float rotateZ)
{
    XMFLOAT3 tempRotate = XMFLOAT3(rotateX * 0.0174532925f, rotateY * 0.0174532925f, rotateZ * 0.0174532925f);

    XMVECTOR resultVector = XMQuaternionRotationRollPitchYaw(tempRotate.x, tempRotate.y, tempRotate.z);

    XMFLOAT3 result;
    XMStoreFloat3(&result, resultVector);
    m_rotation.x += result.x * 57.2957795131f;
    m_rotation.y += result.y * 57.2957795131f;
    m_rotation.z += result.z * 57.2957795131f;

    XMMATRIX resultMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x * 0.0174532925f,
        m_rotation.y * 0.0174532925f,
        m_rotation.z * 0.0174532925f);

    m_modelRight = XMVector3TransformNormal(DefaultRight, resultMatrix);
    m_modelForward = XMVector3TransformNormal(DefaultForward, resultMatrix);
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

void ObjectClass::TranslatePosition(float offsetX, float offsetY, float offsetZ)
{
    m_position.x += offsetX;
    m_position.y += offsetY;
    m_position.z += offsetZ;
}

void ObjectClass::TranslatePosition(XMVECTOR& position)
{
    XMFLOAT3 positionFloat3;
    XMStoreFloat3(&positionFloat3, position);
    m_position.x += positionFloat3.x;
    m_position.y += positionFloat3.y;
    m_position.z += positionFloat3.z;
}

void ObjectClass::SetPosition(float posX, float posY, float posZ)
{
    m_position.x = posX;
    m_position.y = posY;
    m_position.z = posZ;
}

void ObjectClass::SetPosition(const XMFLOAT3& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.z = position.z;
}

void ObjectClass::SetPosition(const XMVECTOR& positionVector)
{
    XMFLOAT3 position;
    XMStoreFloat3(&position, positionVector);
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.z = position.z;
}

void ObjectClass::SetRotation(float rotX, float rotY, float rotZ)
{
    m_rotation.x = rotX;
    m_rotation.y = rotY;
    m_rotation.z = rotZ;

    XMMATRIX resultMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x * 0.0174532925f,
        m_rotation.y * 0.0174532925f,
        m_rotation.z * 0.0174532925f);

    m_modelRight = XMVector3TransformNormal(DefaultRight, resultMatrix);
    m_modelForward = XMVector3TransformNormal(DefaultForward, resultMatrix);
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

void ObjectClass::SetRotation(const XMFLOAT3& rotation)
{
    m_rotation.x = rotation.x;
    m_rotation.y = rotation.y;
    m_rotation.z = rotation.z;

    XMMATRIX resultMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x * 0.0174532925f,
        m_rotation.y * 0.0174532925f,
        m_rotation.z * 0.0174532925f);

    m_modelRight = XMVector3TransformNormal(DefaultRight, resultMatrix);
    m_modelForward = XMVector3TransformNormal(DefaultForward, resultMatrix);
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

void ObjectClass::SetRotation(const XMVECTOR& rotationVector)
{
    XMFLOAT3 rotation;
    XMStoreFloat3(&rotation, rotationVector);
    m_rotation.x = rotation.x;
    m_rotation.y = rotation.y;
    m_rotation.z = rotation.z;

    XMMATRIX resultMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x * 0.0174532925f,
        m_rotation.y * 0.0174532925f,
        m_rotation.z * 0.0174532925f);

    m_modelRight = XMVector3TransformNormal(DefaultRight, resultMatrix);
    m_modelForward = XMVector3TransformNormal(DefaultForward, resultMatrix);
    m_modelUp = XMVector3Cross(m_modelForward, m_modelRight);
}

void ObjectClass::SetScale(float scaleX, float scaleY, float scaleZ)
{
    m_scale.x = scaleX;
    m_scale.y = scaleY;
    m_scale.z = scaleZ;
}

void ObjectClass::SetScale(const XMFLOAT3& scale)
{
    m_scale.x = scale.x;
    m_scale.y = scale.y;
    m_scale.z = scale.z;
}

void ObjectClass::SetScale(const XMVECTOR& scaleVector)
{
    XMFLOAT3 scale;
    XMStoreFloat3(&scale, scaleVector);
    m_scale.x = scale.x;
    m_scale.y = scale.y;
    m_scale.z = scale.z;
}

const XMFLOAT3& ObjectClass::GetPosition()
{
    return m_position;
}

const XMFLOAT3& ObjectClass::GetScale()
{
    return m_scale;
}

const XMFLOAT3& ObjectClass::GetRotation()
{
    return m_rotation;
}

const XMVECTOR& ObjectClass::GetForward()
{
    return m_modelForward;
}

const XMVECTOR& ObjectClass::GetUpVector()
{
    return m_modelUp;
}