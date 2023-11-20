////////////////////////////////////////////////////////////////////////////////
// Filename: textureshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "skyboxshaderclass.h"
#include "DDSTextureLoader.h"

SkyBoxShaderClass::SkyBoxShaderClass()
{
	m_SKYMAP_PS = 0;
	m_SKYMAP_VS = 0;
	m_SKYMAP_VS_Buffer = 0;
	m_SKYMAP_PS_Buffer = 0;
	m_sphereIndexBuffer = 0;
	m_sphereVertBuffer = 0;
	m_Texture = 0;
	m_smrv = 0;

	m_cbPerObjectBuffer = 0;
	m_CCWcullMode = 0;
	m_CubesTexSamplerState = 0;
	m_DSLessEqual = 0;
	m_RSCullNone = 0;
}


SkyBoxShaderClass::SkyBoxShaderClass(const SkyBoxShaderClass& other)
{
}


SkyBoxShaderClass::~SkyBoxShaderClass()
{
}


bool SkyBoxShaderClass::Initialize(ID3D11Device* device, HWND hwnd, CameraClass* camera, IDXGISwapChain* swapChain)
{
	bool result;
	m_Camera = camera;
	m_swapChain = swapChain;
	result = CreateSphere(10, 10, device);
	if (!result) {
		return false;
	}

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"./data/skymap.vs", L"./data/skymap.ps");
	if (!result)
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
	/*
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	*/

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	m_SKYMAP_PS_Buffer = 0;
	m_SKYMAP_VS_Buffer = 0;

	result = D3DCompileFromFile(vsFilename, 0, 0, "SKYMAP_VS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
		&m_SKYMAP_VS_Buffer, &errorMessage);
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
		&m_SKYMAP_PS_Buffer, &errorMessage);
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
	result = device->CreateVertexShader(m_SKYMAP_VS_Buffer->GetBufferPointer(), m_SKYMAP_VS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_VS);
	if (FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(m_SKYMAP_PS_Buffer->GetBufferPointer(), m_SKYMAP_PS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_PS);
	if (FAILED(result))
	{
		return false;
	}

	result = CreateDDSTextureFromFileEx(device, L"./data/skymap.dds", 0, D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE,
		0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&m_Texture, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	m_Texture->GetDesc(&textureDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	viewDesc.TextureCube.MipLevels = textureDesc.MipLevels;
	viewDesc.TextureCube.MostDetailedMip = 0;

	result = device->CreateShaderResourceView(m_Texture, &viewDesc, &m_smrv);
	if (FAILED(result))
	{
		return false;
	}


	D3D11_RASTERIZER_DESC cmdesc;

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.FrontCounterClockwise = true;
	result = device->CreateRasterizerState(&cmdesc, &m_CCWcullMode);
	if (FAILED(result))
	{
		return false;
	}
	cmdesc.FrontCounterClockwise = false;

	//Create the buffer to send to the cbuffer in effect file
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	result = device->CreateBuffer(&cbbd, NULL, &m_cbPerObjectBuffer);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreateRasterizerState(&cmdesc, &m_CWcullMode);
	if (FAILED(result))
	{
		return false;
	}

	cmdesc.CullMode = D3D11_CULL_NONE;
	result = device->CreateRasterizerState(&cmdesc, &m_RSCullNone);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	result = device->CreateDepthStencilState(&dssDesc, &m_DSLessEqual);
	if (FAILED(result))
	{
		return false;
	}

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ID3D11Texture2D* depthStencilBuffer;

	depthStencilDesc.Width = 1600;
	depthStencilDesc.Height = 900;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	

	//Create the Depth/Stencil View
	device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &m_depthStencilView);

	//Create our BackBuffer and Render Target
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBuffer11);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreateRenderTargetView(m_BackBuffer11, NULL, &m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void SkyBoxShaderClass::ShutdownShader()
{
	if (m_SKYMAP_VS_Buffer)
	{
		m_SKYMAP_VS_Buffer->Release();
		m_SKYMAP_VS_Buffer = 0;
	}

	if (m_SKYMAP_PS_Buffer)
	{
		m_SKYMAP_PS_Buffer->Release();
		m_SKYMAP_PS_Buffer = 0;
	}

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

	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = 0;
	}
	if (m_cbPerObjectBuffer)
	{
		m_cbPerObjectBuffer->Release();
		m_cbPerObjectBuffer = 0;
	}
	if (m_CCWcullMode)
	{
		m_CCWcullMode->Release();
		m_CCWcullMode = 0;
	}
	if (m_CubesTexSamplerState)
	{
		m_CubesTexSamplerState->Release();
		m_CubesTexSamplerState = 0;
	}
	if (m_DSLessEqual)
	{
		m_DSLessEqual->Release();
		m_DSLessEqual = 0;
	}
	if (m_RSCullNone)
	{
		m_RSCullNone->Release();
		m_RSCullNone = 0;
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
	cbPerObject cbPerObj;

	XMMATRIX sphereWorld = XMMatrixIdentity();
	XMFLOAT3 cameraPosition = m_Camera->GetPosition();
	sphereWorld *= XMMatrixScaling(10.0f, 10.0f, 10.0f);
	sphereWorld *= XMMatrixTranslationFromVector(XMLoadFloat3(&cameraPosition));

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set our Render Target
	deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Set the default blend state (no blending) for opaque objects
	deviceContext->OMSetBlendState(0, 0, 0xffffffff);

	// Set the spheres index buffer
	deviceContext->IASetIndexBuffer(m_sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the spheres vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &m_sphereVertBuffer, &stride, &offset);

	// Set the world view projection matrix and send it to the constant buffer in effect file
	XMMATRIX WVP = sphereWorld * viewMatrix * projectionMatrix;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	cbPerObj.World = XMMatrixTranspose(sphereWorld);
	deviceContext->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);
	// Send our skymap resource view to pixel shader
	deviceContext->PSSetShaderResources(0, 1, &m_smrv);
	deviceContext->PSSetSamplers(0, 1, &m_CubesTexSamplerState);

	return true;
}


void SkyBoxShaderClass::RenderShader(ID3D11DeviceContext* deviceContext)
{

	// Set the new VS and PS shaders
	deviceContext->VSSetShader(m_SKYMAP_VS, 0, 0);
	deviceContext->PSSetShader(m_SKYMAP_PS, 0, 0);
	// Set the new depth/stencil and RS states
	deviceContext->OMSetDepthStencilState(m_DSLessEqual, 0);
	deviceContext->RSSetState(m_RSCullNone);
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
