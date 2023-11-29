////////////////////////////////////////////////////////////////////////////////
// Filename: textureshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "skyboxshaderclass.h"
#include "DDSTextureLoader.h"

SkyBoxShaderClass::SkyBoxShaderClass()
{
	m_SKYMAP_PS = 0;
	m_SKYMAP_VS = 0;
	m_sphereIndexBuffer = 0;
	m_sphereVertBuffer = 0;
	m_smrv = 0;

	m_matrixBuffer = 0;
}


SkyBoxShaderClass::SkyBoxShaderClass(const SkyBoxShaderClass& other)
{
}


SkyBoxShaderClass::~SkyBoxShaderClass()
{
}


bool SkyBoxShaderClass::Initialize(ID3D11Device* device, HWND hwnd, CameraClass* camera)
{
	bool result;
	m_Camera = camera;

	// Initialize the vertex and pixel shaders.
	result = LoadTexture(device, L"./data/skymap.dds");
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"./data/skymap.vs", L"./data/skymap.ps");
	if (!result)
	{
		return false;
	}

	result = CreateSphere(20, 20, device);
	if (!result) {
		return false;
	}
	return true;
}

bool SkyBoxShaderClass::LoadTexture(ID3D11Device* device, const WCHAR* filename)
{
	bool result;

	ID3D11Texture2D* texture = 0;

	result = CreateDDSTextureFromFileEx(device, L"./data/skymap.dds", 0, D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE,
		0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&texture, nullptr);
	if (FAILED(result)) 
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	// Tell D3D We have a cube texture, which is an array of 2D textures
	// Now we will create the shader resource view description. We will say that this resource view is a texture cube,
	// or an array of 2D textures, so when the pixel shader is texturing a pixel, it will know how to use the 3D 
	// coordinates we give it, which are used to find the texel on the texture cube. Remember a 2D texture uses (u, v)
	// coordinates, well a 3D texture uses (u, v, w) coordinates.
	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = textureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = textureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	// Create the Resource view
	// And finally we create the resource view using the texture we loaded in from a file, the shader resource views 
	// description, and storing the shader resource view in smrv.
	result = device->CreateShaderResourceView(texture, &SMViewDesc, &m_smrv);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void SkyBoxShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}


bool SkyBoxShaderClass::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext);

	return true;
}


bool SkyBoxShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd,
	const WCHAR* vsFilename, const WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;
	D3D11_BUFFER_DESC matrixBufferDesc;

	/*
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	*/

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	SKYMAP_PS_Buffer = 0;
	SKYMAP_VS_Buffer = 0;

	result = D3DCompileFromFile(vsFilename, 0, 0, "SKYMAP_VS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
		&SKYMAP_VS_Buffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = D3DCompileFromFile(psFilename, 0, 0, "SKYMAP_PS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
		&SKYMAP_PS_Buffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}
	
	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(SKYMAP_VS_Buffer->GetBufferPointer(), SKYMAP_VS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_VS);
	if (FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(SKYMAP_PS_Buffer->GetBufferPointer(), SKYMAP_PS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_PS);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);

	//Create the Input Layout
	result = device->CreateInputLayout(layout, numElements, SKYMAP_VS_Buffer->GetBufferPointer(),
		SKYMAP_VS_Buffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	SKYMAP_VS_Buffer->Release();
	SKYMAP_VS_Buffer = 0;

	SKYMAP_PS_Buffer->Release();
	SKYMAP_PS_Buffer = 0;

	
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Describe the Sample State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the Sample State
	result = device->CreateSamplerState(&sampDesc, &m_CubesTexSamplerState);

	return true;
}


void SkyBoxShaderClass::ShutdownShader()
{
	// Release the pixel shader.
	if (m_SKYMAP_PS)
	{
		m_SKYMAP_PS->Release();
		m_SKYMAP_PS = 0;
	}

	// Release the vertex shader.
	if (m_SKYMAP_VS)
	{
		m_SKYMAP_VS->Release();
		m_SKYMAP_VS = 0;
	}

	if(m_smrv)
	{
		m_smrv->Release();
		m_smrv = 0;
	}

	if (m_sphereIndexBuffer)
	{
		m_sphereIndexBuffer->Release();
		m_sphereIndexBuffer = 0;
	}

	if (m_sphereVertBuffer)
	{
		m_sphereVertBuffer->Release();
		m_sphereVertBuffer = 0;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	return;
}


void SkyBoxShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd,
	const WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


bool SkyBoxShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix)
{
	HRESULT result;
	//Set the grounds vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Set the spheres index buffer
	deviceContext->IASetIndexBuffer(m_sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the spheres vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &m_sphereVertBuffer, &stride, &offset);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	XMMATRIX sphereWorld = worldMatrix;
	XMFLOAT3 cameraPosition = m_Camera->GetPosition();
	sphereWorld *= XMMatrixScaling(5.0f, 5.0f, 5.0f);
	sphereWorld *= XMMatrixTranslationFromVector(XMLoadFloat3(&cameraPosition));

	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = sphereWorld;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Send our skymap resource view to pixel shader
	deviceContext->PSSetShaderResources(0, 1, &m_smrv);

	return true;
}


void SkyBoxShaderClass::RenderShader(ID3D11DeviceContext* deviceContext)
{

	//Set the Input Layout
	deviceContext->IASetInputLayout(m_layout);

	// Set the new VS and PS shaders
	deviceContext->VSSetShader(m_SKYMAP_VS, 0, 0);
	deviceContext->PSSetShader(m_SKYMAP_PS, 0, 0);

	deviceContext->PSSetSamplers(0, 1, &m_CubesTexSamplerState);

	deviceContext->DrawIndexed(NumSphereFaces * 3, 0, 0);

	return;
}

bool SkyBoxShaderClass::CreateSphere(int LatLines, int LongLines, ID3D11Device* device)
{
	HRESULT result;

	NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
	NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	vertices.resize(NumSphereVertices);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].pos.x = 0.0f;
	vertices[0].pos.y = 0.0f;
	vertices[0].pos.z = 1.0f;

	XMMATRIX rotationX, rotationY;

	for (DWORD i = 0; i < DWORD(LatLines - 2); ++i)
	{
		spherePitch = (float)(i + 1) * (3.14f / (float)(LatLines - 1));
		rotationX = XMMatrixRotationX(spherePitch);
		for (DWORD j = 0; j < DWORD(LongLines); ++j)
		{
			sphereYaw = (float)j * (6.28f / (float)(LongLines));
			rotationY = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (rotationX * rotationY));
			currVertPos = XMVector3Normalize(currVertPos);
			vertices[i * LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
			vertices[i * LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
			vertices[i * LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[NumSphereVertices - 1].pos.x = 0.0f;
	vertices[NumSphereVertices - 1].pos.y = 0.0f;
	vertices[NumSphereVertices - 1].pos.z = -1.0f;

	
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
	result = device->CreateBuffer( &vertexBufferDesc, &vertexBufferData, &m_sphereVertBuffer);
	if (FAILED(result)) {
		return false;
	}
	

	indices.resize(NumSphereFaces * 3);

	int k = 0;
	for (DWORD l = 0; l < DWORD(LongLines - 1); ++l)
	{
		indices[k] = 0;
		indices[k + 1] = l + 1;
		indices[k + 2] = l + 2;
		k += 3;
	}

	indices[k] = 0;
	indices[k + 1] = LongLines;
	indices[k + 2] = 1;
	k += 3;

	for (DWORD i = 0; i < DWORD(LatLines - 3); ++i)
	{
		for (DWORD j = 0; j < DWORD(LongLines - 1); ++j)
		{
			indices[k] = i * LongLines + j + 1;
			indices[k + 1] = i * LongLines + j + 2;
			indices[k + 2] = (i + 1) * LongLines + j + 1;

			indices[k + 3] = (i + 1) * LongLines + j + 1;
			indices[k + 4] = i * LongLines + j + 2;
			indices[k + 5] = (i + 1) * LongLines + j + 2;

			k += 6; // next quad
		}

		indices[k] = (i * LongLines) + LongLines;
		indices[k + 1] = (i * LongLines) + 1;
		indices[k + 2] = ((i + 1) * LongLines) + LongLines;

		indices[k + 3] = ((i + 1) * LongLines) + LongLines;
		indices[k + 4] = (i * LongLines) + 1;
		indices[k + 5] = ((i + 1) * LongLines) + 1;

		k += 6;
	}

	for (DWORD l = 0; l < (DWORD)(LongLines - 1); ++l)
	{
		indices[k] = NumSphereVertices - 1;
		indices[k + 1] = (NumSphereVertices - 1) - (l + 1);
		indices[k + 2] = (NumSphereVertices - 1) - (l + 2);
		k += 3;
	}

	indices[k] = NumSphereVertices - 1;
	indices[k + 1] = (NumSphereVertices - 1) - LongLines;
	indices[k + 2] = NumSphereVertices - 2;

	
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	result = device->CreateBuffer(&indexBufferDesc, &iinitData, &m_sphereIndexBuffer);
	if(FAILED(result))
	{
		return false;
	}
	
	return true;
}
