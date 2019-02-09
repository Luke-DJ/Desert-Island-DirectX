////////////////////////////////////////////////////////////////////////////////
// Filename: ObjectClass.h
////////////////////////////////////////////////////////////////////////////////

/*
Author: Luke Dicken - Jones
Date: 13/12/2018
*/

#pragma once


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "D3DClass.h"
#include "ShaderManagerClass.h"
#include "LightClass.h"
#include "CameraClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ObjectClass
////////////////////////////////////////////////////////////////////////////////
class ObjectClass
{
public:
	enum ModelType{Model, BumpModel, SpecularModel};

public:
	ObjectClass();
	ObjectClass(ModelType);
	~ObjectClass();

	bool Initialize();

	void Shutdown();

	bool Render();

	ModelType GetModelType();

	ObjectClass* GetParent();
	void SetParent(ObjectClass*);
	void RemoveParent();

	ID3D11Device* GetDevice();
	void SetDevice(ID3D11Device*);

	ID3D11DeviceContext* GetDeviceContext();
	void SetDeviceContext(ID3D11DeviceContext*);

	bool GetCulling();
	bool GetZBuffer();
	void SetCulling(bool);
	void SetZBuffer(bool);

	ShaderManagerClass* GetShaderManager();
	void SetShaderManager(ShaderManagerClass*);

	void SetWorldMatrix(XMMATRIX*);
	void SetViewMatrix(XMMATRIX*);
	void SetProjectionMatrix(XMMATRIX*);

	void SetLight(LightClass*);

	void SetCamera(CameraClass*);

	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetNormal();
	void SetModel(char*);
	void SetTextures(WCHAR*);
	void SetTextures(WCHAR*, WCHAR*);

	bool GetTransparent();
	void SetTransparent(bool);

	void SetTransform(XMMATRIX, XMMATRIX, XMMATRIX);

	XMMATRIX GetTranslation();
	void SetTranslation(float, float, float);
	XMMATRIX GetRotation();
	void SetRotation(float, float, float);
	XMMATRIX GetScale();
	void SetScale(float, float, float);

	XMMATRIX GetSpin();
	void SetSpin(float, float, float);

	XMVECTOR GetWorldTranslationVector();
	XMVECTOR GetWorldRotationVector();
	XMVECTOR GetWorldScaleVector();

	XMFLOAT3 GetWorldTranslation();
	XMFLOAT3 GetWorldRotation();
	XMFLOAT3 GetWorldScale();
	
public:
	ModelType m_ModelType;

	ModelClass* m_Model;
	BumpModelClass* m_BumpModel;
	ModelClass* m_SpecularModel;

private:
	void SetWorldTransform(XMMATRIX* worldMatrix);

	XMMATRIX GetWorldTransform();
	void SetWorldTransformMatrix(XMMATRIX worldTransformMatrix);
	void UpdateWorldTransformVectors();
	void UpdateWorldTransform(XMMATRIX worldMatrix);

	XMMATRIX GetOriginalSpin();
	void SetOriginalSpin(float, float, float);
	XMMATRIX GetCurrentSpin();
	void SetCurrentSpin(XMMATRIX);
	void UpdateSpin();

private:
	// A pointer to the object's parent
	ObjectClass* m_Parent;

	// A pointer to the device
	ID3D11Device* m_Device;
	// A pointer to the device context
	ID3D11DeviceContext* m_DeviceContext;

	// A boolean indicating whether this object will use culling
	bool m_Culling;
	// A boolean indicating whether this object will use the z buffer
	bool m_ZBuffer;

	// A pointer to the shader manager class
	ShaderManagerClass* m_ShaderManager;

	// A pointer to the world matrix
	XMMATRIX* m_WorldMatrix;
	// A pointer to the view matrix
	XMMATRIX* m_ViewMatrix;
	// A pointer to the projection matrix
	XMMATRIX* m_ProjectionMatrix;

	// A pointer to the light class
	LightClass* m_Light;
	// A pointer to the camera class
	CameraClass* m_Camera;

	// A pointer to the file name of the object's model
	char* m_ModelFilename;
	// A pointer to the file name of the diffuse texture of the object's model
	WCHAR* m_DiffuseFilename;
	// A pointer to the file name of the normal map of the object's model
	WCHAR* m_NormalFilename;

	// A boolean indicating whether this object will render transparent regions of its texture as transparent
	bool m_Transparent;

	// The object's original translation matrix
	XMMATRIX m_TranslateMatrix;
	// The object's original rotation matrix
	XMMATRIX m_RotationMatrix;
	// The object's original scale matrix
	XMMATRIX m_ScaleMatrix;

	// The object's original spin matrix
	XMMATRIX m_SpinMatrix;
	// The object's current spin matrix
	XMMATRIX m_CurrentSpinMatrix;

	// The object's world transform matrix
	XMMATRIX m_WorldTransformMatrix;
	// The object's world translation matrix
	XMVECTOR m_WorldTranslationVector;
	// The object's world rotation matrix
	XMVECTOR m_WorldRotationVector;
	// The object's world scale matrix
	XMVECTOR m_WorldScaleVector;
};
