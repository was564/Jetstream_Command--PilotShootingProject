////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"
#include "graphicsclass.h"

CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;

	m_camForward = DefaultForward;
	m_camRight = DefaultRight;
	
	m_distance = 4.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void CameraClass::SetPosition(const XMFLOAT3& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.z = position.z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void CameraClass::MoveForward(float speed)
{
	XMFLOAT3 temp;
	XMStoreFloat3(&temp, m_camForward);
	m_position.x += temp.x * speed;
	m_position.y += temp.y * speed;
	m_position.z += temp.z * speed;
}

void CameraClass::MoveRight(float speed)
{
	XMFLOAT3 temp;
	XMStoreFloat3(&temp, m_camRight);
	m_position.x += temp.x * speed;
	m_position.y += temp.y * speed;
	m_position.z += temp.z * speed;
}

void CameraClass::Move(const XMVECTOR& direction, float speed)
{
	XMFLOAT3 temp;
	XMStoreFloat3(&temp, direction);
	m_position.x += temp.x * speed;
	m_position.y += temp.y * speed;
	m_position.z += temp.z * speed;
}

void CameraClass::Rotate(float rotateX, float rotateY, float rotateZ)
{
	XMFLOAT3 tempRight, tempForward;
	XMStoreFloat3(&tempRight, m_camRight);
	XMStoreFloat3(&tempForward, m_camForward);

	m_rotation.x += rotateX;
	m_rotation.y += rotateY;
	m_rotation.z += rotateZ;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}



XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

XMFLOAT3 CameraClass::GetActualPosition()
{
    XMVECTOR position = XMLoadFloat3(&m_position);
    position -= m_camForward * m_distance;

    XMFLOAT3 positionFloat;
    XMStoreFloat3(&positionFloat, position);
    return XMFLOAT3(positionFloat);
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	lookAt = XMVector3Normalize(lookAt);
	up = XMVector3TransformCoord(up, rotationMatrix);
	
	m_camRight = XMVector3TransformCoord(DefaultRight, rotationMatrix);
	m_camForward = XMVector3TransformCoord(DefaultForward, rotationMatrix);
	m_camUp = XMVector3Cross(m_camForward, m_camRight);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt + XMVectorSet(0.0f, 2.0f, 0.0f, 1.0f);

	m_LookAtPosition = position;
	position = position - m_camForward * m_distance;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

const XMVECTOR& CameraClass::GetLookAtPosition()
{
	return m_LookAtPosition;
}

