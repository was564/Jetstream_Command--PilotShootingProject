////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>

#include "AlignedAllocationPolicy.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass : public AlignedAllocationPolicy<16>
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetPosition(const XMFLOAT3&);
	void SetRotation(float, float, float);
    void SetRotation(const XMFLOAT3&);

	void MoveForward(float);
	void MoveRight(float);
	void Move(const XMVECTOR&, float);
	void Rotate(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

    XMFLOAT3 GetActualPosition();

	void Render();
	void GetViewMatrix(XMMATRIX&);
	const XMVECTOR& GetLookAtPosition();

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;

	XMVECTOR m_camRight;
	XMVECTOR m_camForward;
	XMVECTOR m_camUp;

	XMVECTOR m_LookAtPosition;

	float m_distance;
};

#endif