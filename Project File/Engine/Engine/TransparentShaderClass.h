////////////////////////////////////////////////////////////////////////////////
// Filename: transparentshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TRANSPARENTSHADERCLASS_H_
#define _TRANSPARENTSHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
using namespace DirectX;

#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: TransparentShaderClass
////////////////////////////////////////////////////////////////////////////////
class TransparentShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	// A buffer type that matches the constant buffer inside the pixel shader (12 bytes of padding are added so CreateBuffer won't fail)
	struct TransparentBufferType
	{
		float blendAmount;
		XMFLOAT3 padding;
	};

public:
	TransparentShaderClass();
	TransparentShaderClass(const TransparentShaderClass&);
	~TransparentShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;

	// A new buffer variable that provides an interface to the blendAmount value inside the transparency shader
	ID3D11Buffer* m_transparentBuffer;
};

#endif