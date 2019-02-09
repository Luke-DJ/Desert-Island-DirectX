////////////////////////////////////////////////////////////////////////////////
// Filename: SceneClass.h
////////////////////////////////////////////////////////////////////////////////

/*
Author: Luke Dicken - Jones
Date: 13/12/2018
*/

#pragma once


//////////////
// INCLUDES //
//////////////
#include <vector>
#include <algorithm>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "ObjectClass.h"
#include "CameraClass.h"
#include "LightClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: SceneClass
////////////////////////////////////////////////////////////////////////////////
class SceneClass
{
public:
	SceneClass();
	~SceneClass();

	bool AddObject(string, ObjectClass*);
	bool RemoveObject(string);

	vector<pair<string, ObjectClass*>>* GetWorldObjects();
	ObjectClass* GetWorldObject(string);
	int GetWorldObjectIndex(string);

	bool InitializeObjects();
	void ShutdownObjects();
	bool RenderObjects(D3DClass*, CameraClass*, XMMATRIX*, XMMATRIX*, XMMATRIX*, LightClass*);

private:
	// A vector container for the world objects
	vector<pair<string, ObjectClass*>>* worldObjects;
};
