#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class ObjectClass abstract
{
public:
    ObjectClass();
    ~ObjectClass();

    virtual void Render(ID3D11DeviceContext*) = 0;
    virtual int GetIndexCount() = 0;

    virtual ID3D11ShaderResourceView* GetTexture() = 0;
    virtual ID3D11ShaderResourceView* GetTexture1() { return nullptr; };
    virtual ID3D11ShaderResourceView* GetTexture2() { return nullptr; };
    virtual ID3D11ShaderResourceView* GetTexture3() { return nullptr; };

    void Rotate(float, float, float);

    void TranslatePosition(float, float, float);
    void TranslatePosition(XMVECTOR&);
    void SetPosition(float, float, float);
    void SetPosition(const XMFLOAT3&);
    void SetPosition(const XMVECTOR&);
    void SetRotation(float, float, float);
    void SetRotation(const XMFLOAT3&);
    void SetRotation(const XMVECTOR&);
    void SetScale(float, float, float);
    void SetScale(const XMFLOAT3&);
    void SetScale(const XMVECTOR&);
    const XMFLOAT3& GetPosition();
    const XMFLOAT3& GetScale();
    const XMFLOAT3& GetRotation();
    const XMVECTOR& GetForward();
    const XMVECTOR& GetUpVector();

private:
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;
    XMFLOAT3 m_scale;

    XMVECTOR m_modelForward;
    XMVECTOR m_modelRight;
    XMVECTOR m_modelUp;
};

