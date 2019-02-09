////////////////////////////////////////////////////////////////////////////////
// Filename: ObjectClass.cpp
////////////////////////////////////////////////////////////////////////////////

/*
Author: Luke Dicken - Jones
Date: 13/12/2018
*/

#include "ObjectClass.h"
#include <math.h>


// Calling the constructor with the standard model type parameter if no model type is specified
ObjectClass::ObjectClass()
{
	ObjectClass::ObjectClass(Model);
}

ObjectClass::ObjectClass(ModelType modelType)
{
	// Setting up default values for this object's variables

	m_ModelType = modelType;

	m_Model = 0;
	m_BumpModel = 0;
	m_SpecularModel = 0;

	if (m_ModelType == Model)
	{
		m_Model = new ModelClass;
	}
	else if (m_ModelType == BumpModel)
	{
		m_BumpModel = new BumpModelClass;
	}
	else if (m_ModelType == SpecularModel)
	{
		m_SpecularModel = new ModelClass;
	}

	m_Parent = 0;
	m_Device = 0;
	m_DeviceContext = 0;
	m_Culling = true;
	m_ZBuffer = true;
	m_ShaderManager = 0;
	m_WorldMatrix = 0;
	m_ViewMatrix = 0;
	m_ProjectionMatrix = 0;
	m_Light = 0;
	m_Camera = 0;
	m_ModelFilename = 0;
	m_DiffuseFilename = 0;
	m_NormalFilename = 0;
	m_Transparent = false;
	m_TranslateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	m_ScaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	m_SpinMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	m_CurrentSpinMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
}

ObjectClass::~ObjectClass()
{
}

bool ObjectClass::Initialize()
{
	bool result;

	// Using different initialize parameters based on the object's type

	if (GetModelType() == Model && m_Model)
	{
		result = m_Model->Initialize(m_Device, m_ModelFilename, m_DiffuseFilename);
	}
	else if (GetModelType() == BumpModel && m_BumpModel)
	{
		result = m_BumpModel->Initialize(m_Device, m_ModelFilename, m_DiffuseFilename, m_NormalFilename);
	}
	else if (GetModelType() == SpecularModel && m_SpecularModel)
	{
		result = m_SpecularModel->Initialize(m_Device, m_ModelFilename, m_DiffuseFilename);
	}

	return result;
}

void ObjectClass::Shutdown()
{
	// Release the standard model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the bump model object.
	if (m_BumpModel)
	{
		m_BumpModel->Shutdown();
		delete m_BumpModel;
		m_BumpModel = 0;
	}

	// Release the specular model object.
	if (m_SpecularModel)
	{
		m_SpecularModel->Shutdown();
		delete m_SpecularModel;
		m_SpecularModel = 0;
	}
}

bool ObjectClass::Render()
{
	bool result;

	// Setting the world matrix to the required transform for this object
	SetWorldTransform(m_WorldMatrix);

	// Using different render methods/parameters based on the object's type

	if (GetModelType() == Model && m_Model)
	{
		m_Model->Render(m_DeviceContext);
		result = GetShaderManager()->RenderTextureShader(m_DeviceContext, m_Model->GetIndexCount(), *m_WorldMatrix, *m_ViewMatrix, *m_ProjectionMatrix, m_Model->GetTexture());
	}
	else if (GetModelType() == BumpModel && m_BumpModel)
	{
		m_BumpModel->Render(m_DeviceContext);
		result = GetShaderManager()->RenderBumpMapShader(m_DeviceContext, m_BumpModel->GetIndexCount(), *m_WorldMatrix, *m_ViewMatrix, *m_ProjectionMatrix, m_BumpModel->GetColorTexture(), m_BumpModel->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	}
	else if (GetModelType() == SpecularModel && m_SpecularModel)
	{
		m_SpecularModel->Render(m_DeviceContext);
		result = GetShaderManager()->RenderLightShader(m_DeviceContext, m_SpecularModel->GetIndexCount(), *m_WorldMatrix, *m_ViewMatrix, *m_ProjectionMatrix, m_SpecularModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}

	return result;
}

ObjectClass::ModelType ObjectClass::GetModelType()
{
	return m_ModelType;
}

ObjectClass* ObjectClass::GetParent()
{
	return m_Parent;
}

void ObjectClass::SetParent(ObjectClass* parent)
{
	m_Parent = parent;
}

void ObjectClass::RemoveParent()
{
	m_Parent = 0;
}

ID3D11Device* ObjectClass::GetDevice()
{
	return m_Device;
}

void ObjectClass::SetDevice(ID3D11Device* device)
{
	m_Device = device;
}

ID3D11DeviceContext* ObjectClass::GetDeviceContext()
{
	return m_DeviceContext;
}

void ObjectClass::SetDeviceContext(ID3D11DeviceContext* deviceContext)
{
	m_DeviceContext = deviceContext;
}

bool ObjectClass::GetCulling()
{
	return m_Culling;
}

bool ObjectClass::GetZBuffer()
{
	return m_ZBuffer;
}

void ObjectClass::SetCulling(bool culling)
{
	m_Culling = culling;
}

void ObjectClass::SetZBuffer(bool zBuffer)
{
	m_ZBuffer = zBuffer;
}

ShaderManagerClass* ObjectClass::GetShaderManager()
{
	return m_ShaderManager;
}

void ObjectClass::SetShaderManager(ShaderManagerClass* shaderManager)
{
	m_ShaderManager = shaderManager;
}

void ObjectClass::SetWorldMatrix(XMMATRIX* worldMatrix)
{
	m_WorldMatrix = worldMatrix;
}

void ObjectClass::SetViewMatrix(XMMATRIX* viewMatrix)
{
	m_ViewMatrix = viewMatrix;
}

void ObjectClass::SetProjectionMatrix(XMMATRIX* projectionMatrix)
{
	m_ProjectionMatrix = projectionMatrix;
}

void ObjectClass::SetLight(LightClass* light)
{
	m_Light = light;
}

void ObjectClass::SetCamera(CameraClass* camera)
{
	m_Camera = camera;
}

ID3D11ShaderResourceView* ObjectClass::GetTexture()
{
	ID3D11ShaderResourceView* result;

	// Using different methods for retrieving the texture based on the object's type

	if (GetModelType() == Model && m_ModelType)
	{
		result = m_Model->GetTexture();
	}
	else if (GetModelType() == BumpModel && m_BumpModel)
	{
		result = m_BumpModel->GetColorTexture();
	}
	else if (GetModelType() == SpecularModel && m_SpecularModel)
	{
		result = m_SpecularModel->GetTexture();
	}

	return result;
}

ID3D11ShaderResourceView* ObjectClass::GetNormal()
{
	ID3D11ShaderResourceView* result;

	// Retrieving the normal map texture if the object is of the bump model type

	if (GetModelType() == BumpModel && m_BumpModel)
	{
		result = m_BumpModel->GetNormalMapTexture();
	}

	return result;
}

void ObjectClass::SetModel(char* modelFilename)
{
	m_ModelFilename = modelFilename;
}

void ObjectClass::SetTextures(WCHAR* diffuseFilename)
{
	m_DiffuseFilename = diffuseFilename;
}

void ObjectClass::SetTextures(WCHAR* diffuseFilename, WCHAR* normalFilename)
{
	SetTextures(diffuseFilename);
	m_NormalFilename = normalFilename;
}

bool ObjectClass::GetTransparent()
{
	return m_Transparent;
}

void ObjectClass::SetTransparent(bool transparent)
{
	m_Transparent = transparent;
}

void ObjectClass::SetTransform(XMMATRIX translateMatrix, XMMATRIX rotationMatrix, XMMATRIX scaleMatrix)
{
	m_TranslateMatrix = translateMatrix;
	m_RotationMatrix = rotationMatrix;
	m_ScaleMatrix = scaleMatrix;
}

XMMATRIX ObjectClass::GetTranslation()
{
	return m_TranslateMatrix;
}

void ObjectClass::SetTranslation(float x, float y, float z)
{
	m_TranslateMatrix = XMMatrixTranslation(x, y, z);
}

XMMATRIX ObjectClass::GetRotation()
{
	return m_RotationMatrix;
}

void ObjectClass::SetRotation(float x, float y, float z)
{
	m_RotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(x), XMConvertToRadians(y), XMConvertToRadians(z));
}

XMMATRIX ObjectClass::GetScale()
{
	return m_ScaleMatrix;
}

void ObjectClass::SetScale(float x, float y, float z)
{
	m_ScaleMatrix = XMMatrixScaling(x, y, z);
}

XMMATRIX ObjectClass::GetSpin()
{
	return GetOriginalSpin();
}

void ObjectClass::SetSpin(float x, float y, float z)
{
	SetOriginalSpin(x, y, z);
	SetCurrentSpin(GetOriginalSpin());
}

XMVECTOR ObjectClass::GetWorldTranslationVector()
{
	return m_WorldTranslationVector;
}

XMVECTOR ObjectClass::GetWorldRotationVector()
{
	return m_WorldRotationVector;
}

XMVECTOR ObjectClass::GetWorldScaleVector()
{
	return m_WorldScaleVector;
}

// Methods that convert and return the stored vectors for world translation, rotation, and scale

XMFLOAT3 ObjectClass::GetWorldTranslation()
{
	XMFLOAT3 worldTranslation;
	XMStoreFloat3(&worldTranslation, GetWorldTranslationVector());
	return worldTranslation;
}

XMFLOAT3 ObjectClass::GetWorldRotation()
{
	XMFLOAT3 worldRotation;
	XMStoreFloat3(&worldRotation, GetWorldRotationVector());
	return worldRotation;
}

XMFLOAT3 ObjectClass::GetWorldScale()
{
	XMFLOAT3 worldScale;
	XMStoreFloat3(&worldScale, GetWorldScaleVector());
	return worldScale;
}


void ObjectClass::SetWorldTransform(XMMATRIX* worldMatrix)
{
	// Applying the object's scale, rotation, spin, and translation to the world matrix
	*worldMatrix = XMMatrixMultiply(*worldMatrix, GetScale());
	*worldMatrix = XMMatrixMultiply(*worldMatrix, GetRotation());
	*worldMatrix = XMMatrixMultiply(*worldMatrix, GetCurrentSpin());
	*worldMatrix = XMMatrixMultiply(*worldMatrix, GetTranslation());

	// Iterating up the parental hierarchy, applying each parent's rotation, spin, and translation to the world matrix
	ObjectClass* currentParent = m_Parent;
	while (currentParent)
	{
		*worldMatrix = XMMatrixMultiply(*worldMatrix, currentParent->GetRotation());
		*worldMatrix = XMMatrixMultiply(*worldMatrix, currentParent->GetCurrentSpin());
		*worldMatrix = XMMatrixMultiply(*worldMatrix, currentParent->GetTranslation());

		currentParent = currentParent->GetParent();
	}

	// Updating the stored world transform values of this object
	UpdateWorldTransform(*worldMatrix);

	// Updating the spin value
	UpdateSpin();
}

XMMATRIX ObjectClass::GetWorldTransform()
{
	return m_WorldTransformMatrix;
}

void ObjectClass::SetWorldTransformMatrix(XMMATRIX worldTransformMatrix)
{
	m_WorldTransformMatrix = worldTransformMatrix;
}

void ObjectClass::UpdateWorldTransformVectors()
{
	// Extrating information from the world transform matrix to the existing world scale, rotation, and translation vectors
	XMMatrixDecompose(&m_WorldScaleVector, &m_WorldRotationVector, &m_WorldTranslationVector, GetWorldTransform());
}

void ObjectClass::UpdateWorldTransform(XMMATRIX worldMatrix)
{
	SetWorldTransformMatrix(worldMatrix);
	UpdateWorldTransformVectors();
}

XMMATRIX ObjectClass::GetOriginalSpin()
{
	return m_SpinMatrix;
}

void ObjectClass::SetOriginalSpin(float x, float y, float z)
{
	m_SpinMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(x), XMConvertToRadians(y), XMConvertToRadians(z));
}

XMMATRIX ObjectClass::GetCurrentSpin()
{
	return m_CurrentSpinMatrix;
}

void ObjectClass::SetCurrentSpin(XMMATRIX spinMatrix)
{
	m_CurrentSpinMatrix = spinMatrix;
}

void ObjectClass::UpdateSpin()
{
	/* An attempt at keeping the rotation values normalized (needs further analysis)

	XMMATRIX newCurrentSpin = XMMatrixMultiply(GetCurrentSpin(), GetOriginalSpin());

	XMVECTOR scaleVector, rotationVector, translationVector;
	XMMatrixDecompose(&scaleVector, &rotationVector, &translationVector, newCurrentSpin);

	XMQuaternionNormalize(rotationVector);

	newCurrentSpin.r[3] = rotationVector;

	SetCurrentSpin(newCurrentSpin); */


	SetCurrentSpin(XMMatrixMultiply(GetCurrentSpin(), GetOriginalSpin()));
}
