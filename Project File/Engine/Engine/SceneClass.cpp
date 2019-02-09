////////////////////////////////////////////////////////////////////////////////
// Filename: SceneClass.cpp
////////////////////////////////////////////////////////////////////////////////

/*
Author: Luke Dicken - Jones
Date: 13/12/2018
*/

#include "SceneClass.h"


SceneClass::SceneClass()
{
	// Initializing the world objects vector container
	worldObjects = new vector<pair<string, ObjectClass*>>();
}

SceneClass::~SceneClass()
{
}

bool SceneClass::AddObject(string name, ObjectClass* object)
{
	// Returning false if a world object already exists with the given name
	if (GetWorldObject(name))
	{
		return false;
	}

	// Adding the world object to the end of the world objects vector container
	(*GetWorldObjects()).push_back(pair<string, ObjectClass*>(name, object));

	return true;
}

bool SceneClass::RemoveObject(string name)
{
	vector<pair<string, ObjectClass*>>* worldObjects = GetWorldObjects();
	int index = GetWorldObjectIndex(name);

	// Returning false if an index position for a world object matching the given name can't be found
	if (index == worldObjects->size())
	{
		return false;
	}

	// Removing the world object from the world objects vector container
	worldObjects->erase(worldObjects->begin() + index);

	return true;
}

bool SceneClass::InitializeObjects()
{
	// Iterating over the world objects vector container, and initializing each object
	for (auto worldObject : *GetWorldObjects())
	{
		if (!(worldObject.second->Initialize()))
		{
			return false;
		}
	}

	return true;
}

vector<pair<string, ObjectClass*>>* SceneClass::GetWorldObjects()
{
	return worldObjects;
}

ObjectClass* SceneClass::GetWorldObject(string name)
{
	ObjectClass* object = 0;

	// Iterating over the world objects vector container until an object is found that matches the given name
	for (auto worldObject : *GetWorldObjects())
	{
		if (worldObject.first == name)
		{
			object = worldObject.second;
			break;
		}
	}

	// Returning the matching object
	return object;
}

int SceneClass::GetWorldObjectIndex(string name)
{
	vector<pair<string, ObjectClass*>>* worldObjects = GetWorldObjects();
	int worldObjectsCount = worldObjects->size();

	// Iterating over the world objects vector container until an object is found that matches the given name
	for (int i = 0; i < worldObjectsCount; i++)
	{
		if ((*worldObjects)[i].first == name)
		{
			// Returning the matching object
			return i;
		}
	}

	// Returning an invalid index position if no matching object is found
	return worldObjectsCount;
}

void SceneClass::ShutdownObjects()
{
	// Iterating over the world objects vector container, and shutting down each object
	for (auto worldObject : *GetWorldObjects())
	{
		worldObject.second->Shutdown();
	}
}

bool SceneClass::RenderObjects(D3DClass* D3D, CameraClass* camera, XMMATRIX* worldMatrix, XMMATRIX* viewMatrix, XMMATRIX* projectionMatrix, LightClass* light)
{
	// Iterating over the world objects vector container
	for (auto worldObject : *GetWorldObjects())
	{
		ObjectClass* object = worldObject.second;
		ObjectClass::ModelType modelType = object->GetModelType();

		D3D->GetWorldMatrix(*worldMatrix);
		camera->GetViewMatrix(*viewMatrix);
		D3D->GetProjectionMatrix(*projectionMatrix);
		// Enabling/disabling certain D3DClass values based on the object's preferences
		if (object->GetCulling())
		{
			D3D->TurnOnCulling();
		}
		else
		{
			D3D->TurnOffCulling();
		}
		if (object->GetZBuffer())
		{
			D3D->TurnZBufferOn();
		}
		else
		{
			D3D->TurnZBufferOff();
		}
		if (object->GetTransparent())
		{
			D3D->TurnOnAlphaBlending();
		}
		else
		{
			D3D->TurnOffAlphaBlending();
		}

		object->SetDeviceContext(D3D->GetDeviceContext());
		object->SetWorldMatrix(worldMatrix);
		object->SetViewMatrix(viewMatrix);
		object->SetProjectionMatrix(projectionMatrix);
		// Setting model type specific values
		if (modelType == ObjectClass::ModelType::BumpModel || modelType == ObjectClass::ModelType::SpecularModel)
		{
			object->SetLight(light);
		}
		if (modelType == ObjectClass::ModelType::SpecularModel)
		{
			object->SetCamera(camera);
		}

		// Rendering the object
		if (!(object->Render()))
		{
			return false;
		}

		// Setting certain D3DClass values back to their defaults
		D3D->TurnOnCulling();
		D3D->TurnZBufferOn();
		D3D->TurnOffAlphaBlending();
	}

	return true;
}
