#include "skyboxclass.h"
#include "DDSTextureLoader.h"

SkyBoxClass::SkyBoxClass()
{
	m_sphereIndexBuffer = 0;
	m_Texture = 0;
}

SkyBoxClass::SkyBoxClass(const SkyBoxClass&)
{
}

SkyBoxClass::~SkyBoxClass()
{
}

bool SkyBoxClass::Initialize(ID3D11Device* device, const WCHAR* fileName)
{
	HRESULT result;
	result = CreateDDSTextureFromFileEx(device, fileName, 0, D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE,
		0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&m_Texture, nullptr);
	if (!result)
	{
		return false;
	}
	return true;
}

void SkyBoxClass::Shutdown()
{
	if (m_sphereIndexBuffer)
	{
		m_sphereIndexBuffer->Release();
		delete m_sphereIndexBuffer;
	}

	if (m_Texture)
	{
		m_Texture->Release();
		delete m_Texture;
	}
}

ID3D11Resource* SkyBoxClass::GetTexture()
{
	return m_Texture;
}

bool SkyBoxClass::CreateSphere(int LatLines, int LongLines, ID3D11Device* device)
{
	HRESULT result;

	NumSphereVertices = ((LatLines-2) * LongLines) + 2;
	NumSphereFaces  = ((LatLines-3)*(LongLines)*2) + (LongLines*2);

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	vertices.resize(NumSphereVertices);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].pos.x = 0.0f;
	vertices[0].pos.y = 0.0f;
	vertices[0].pos.z = 1.0f;

	XMMATRIX rotationX, rotationY;

	for(DWORD i = 0; i < DWORD(LatLines-2); ++i)
	{
		spherePitch = (float)(i+1) * (3.14f/(float)(LatLines-1));
		rotationX = XMMatrixRotationX(spherePitch);
		for(DWORD j = 0; j < DWORD(LongLines); ++j)
		{
			sphereYaw = (float)j * (6.28f/(float)(LongLines));
			rotationY = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal( XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (rotationX * rotationY) );	
			currVertPos = XMVector3Normalize( currVertPos );
			vertices[i*LongLines+j+1].pos.x = XMVectorGetX(currVertPos);
			vertices[i*LongLines+j+1].pos.y = XMVectorGetY(currVertPos);
			vertices[i*LongLines+j+1].pos.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[NumSphereVertices-1].pos.x =  0.0f;
	vertices[NumSphereVertices-1].pos.y =  0.0f;
	vertices[NumSphereVertices-1].pos.z = -1.0f;

	/*
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof( Vertex ) * NumSphereVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData; 

	ZeroMemory( &vertexBufferData, sizeof(vertexBufferData) );
	vertexBufferData.pSysMem = &vertices[0];
	result = device->CreateBuffer( &vertexBufferDesc, &vertexBufferData, &sphereVertBuffer);
	if (!result) {
		return false;
	}
	*/

	indices.resize(NumSphereFaces * 3);

	int k = 0;
	for(DWORD l = 0; l < DWORD(LongLines-1); ++l)
	{
		indices[k] = 0;
		indices[k+1] = l+1;
		indices[k+2] = l+2;
		k += 3;
	}

	indices[k] = 0;
	indices[k+1] = LongLines;
	indices[k+2] = 1;
	k += 3;

	for(DWORD i = 0; i < DWORD(LatLines-3); ++i)
	{
		for(DWORD j = 0; j < DWORD(LongLines-1); ++j)
		{
			indices[k]   = i*LongLines+j+1;
			indices[k+1] = i*LongLines+j+2;
			indices[k+2] = (i+1)*LongLines+j+1;

			indices[k+3] = (i+1)*LongLines+j+1;
			indices[k+4] = i*LongLines+j+2;
			indices[k+5] = (i+1)*LongLines+j+2;

			k += 6; // next quad
		}

		indices[k]   = (i*LongLines)+LongLines;
		indices[k+1] = (i*LongLines)+1;
		indices[k+2] = ((i+1)*LongLines)+LongLines;

		indices[k+3] = ((i+1)*LongLines)+LongLines;
		indices[k+4] = (i*LongLines)+1;
		indices[k+5] = ((i+1)*LongLines)+1;

		k += 6;
	}

	for(DWORD l = 0; l < (DWORD)(LongLines-1); ++l)
	{
		indices[k] = NumSphereVertices-1;
		indices[k+1] = (NumSphereVertices-1)-(l+1);
		indices[k+2] = (NumSphereVertices-1)-(l+2);
		k += 3;
	}

	indices[k] = NumSphereVertices-1;
	indices[k+1] = (NumSphereVertices-1)-LongLines;
	indices[k+2] = NumSphereVertices-2;

	/*
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	result = device->CreateBuffer(&indexBufferDesc, &iinitData, &sphereIndexBuffer);
	if(!result)
	{
		return false;
	}
	*/
	return true;
}
